#!/usr/bin/perl

# TODO list:
# @assert tcsh boolean expression

unless (@ARGV >= 1) 
{
    print_help_and_exit();
}

use strict;
use warnings;

use File::Basename;
use File::Copy::Recursive qw(rcopy fcopy);
use Cwd;
use Cwd 'abs_path';

undef my %torun;

my $DBG = 0;
my($filename, $rvtestdir) = fileparse("$0");
my $conf = "$rvtestdir" . "rvtest.txt";
my $test_srcdir;
my %value = ("difflags" => "",
             "may_change_sources" => 0,
             "rvt" => abs_path(shift(@ARGV)),
             "run_dir" => getcwd(),
             "global_rvt_args" => ""
            );
my $cur_test_failed = 0;
my @failed_tests = ();
my @files_to_compare = ();

$SIG{INT} = \&ctrl_C;

run_tests("$conf", @ARGV);

sub run_tests {
    my $conf = shift;
    my @instrs;
    my $begun = 0;
    my @args = parse_command_line_options(@_);

    %torun = get_test_names($conf, @args);
    my $n_tests = scalar keys %torun;

    #`rm -f fail.log`;
    open(INCONF, "< " . "$conf");
    readconfline: while(<INCONF>) {
        next readconfline if /^#/; #skip comments
        if (/^\@test/) {
	    my $newtestname = $_;
            $begun == 1 && run_next_test($n_tests, @instrs);
            $begun = 1;
            @instrs = ($newtestname);
        }
        else {
            push(@instrs, $_);
        }
    }
    $begun == 1 && run_next_test($n_tests, @instrs);
    close(INCONF);

    create_fail_log(@failed_tests);
}

sub run_next_test {
    $DBG && print "args for test: " . "@_" . "\n";
    my %save_value = %value;
    my $test = run_next_test_low(@_);
    my @resstr = ("result: SUCCESS\n", "result: FAILURE\n", "");
    print $resstr[$cur_test_failed];
    delete $torun{$test};
    %value = %save_value;
}

sub run_next_test_low {
    my $n_all_tests = shift;
    my $test = shift;
    my @instrs = @_;
    my $cur;

    my @testinstr = split(/\s+/, $test);
    $test = $testinstr[1];
    $cur_test_failed = 2;
    return $test unless defined $torun{$test};
    print "running test: ".$test." (".($n_all_tests-keys(%torun)+1)."/".$n_all_tests.")...\n";
    $cur_test_failed = 0;
    
    `rm -rf $test`;
    $test_srcdir = $rvtestdir . "tests/" . $test;
    rcopy($test_srcdir, $test) || return test_failed($test, "could not create the directory ./" . $test);
    my $cwd = getcwd();
    chdir($test) || return test_failed($test, "could not enter the directory ./" . $test);

    @instrs = update_instructions(@instrs);
    while (@instrs) {
        $cur = shift(@instrs); 
        $DBG && print "cur = " . $cur;
        assign_get_instrs($cur);
        $cur =~ /^\@/ ? run_spec_instr($cur) : system($cur);
    }
    chdir($cwd);
    #!$DBG && `rm -rf $test` if ($cur_test_failed == 0);
    return $test;
}

sub assign_get_instrs {
    foreach my $literal (@_) {
        while($literal =~ /^(.*)\@get\((\S+)\)(.*)$/) {
            my $var_ = $2;
            $DBG && print "Before get instruction: ".$literal."\n";
            $literal =~ s/\@get\($var_\)/$value{$var_}/g;
            $DBG && print "After get instruction: ".$literal." \n";
        }
    }
}

sub run_rvt {
    my @rvt_args = (@_);
    my $src1 = pop(@rvt_args);
    my $src0 = pop(@rvt_args);
    open(rvt_com, ">rvt.sh");
    $value{"may_change_sources"} || print rvt_com "mkdir -p proto; cp -pf \"".$src0."\" \"".$src1."\" proto \n"; 
    print rvt_com "\"".$value{"rvt"}."\" ".$value{"global_rvt_args"}." @rvt_args";
    print rvt_com " \"".$src0."\" \"".$src1."\" >& out \n";
    print rvt_com "echo -n \$status > .status\n";
    close(rvt_com);

    `tcsh -f rvt.sh`;
    
    my $exit_status = 1;
    open(STATUS, "<.status") || return io_failure("could not determine the exit status of rvt");
    $exit_status = $_ while(<STATUS>);
    close(STATUS); 
    `rm -f .status`;
     
    $exit_status == 0 || return io_failure("rvt terminated with status " . $exit_status);
    $value{"may_change_sources"} || compare_source_files($src0, $src1);
}

sub compare_source_files {
    my $save_difflags = $value{"difflags"};
    push(@files_to_compare, join("#", @_));
    $value{"difflags"} = "--strip-trailing-cr";
    compare_low("Source file ", " is changed. You can cancel this check with: \@set may_change_sources = 1");
    $value{"difflags"} = $save_difflags;
}

sub compare_low {
    my ($premsg, $postmsg) = @_;
    my $f;
    my @cmpfiles = split('#', pop(@files_to_compare));
    COMPARE: foreach $f (@cmpfiles) {
        if (!(-f $f)) {
            io_failure("Comparison file ".$f." was not generated");
            next COMPARE;
        }
        my @f_path = split(/\//, $f);
        my $filename = pop(@f_path);
        if (!(-f "proto/".$filename)) {
            io_failure("Reference file ".$filename." is not found");
            next COMPARE;
        }
        dos2unix($f, $filename);
        dos2unix("proto/".$filename, $filename);
        $DBG && print "Comparing file: ".$f." \n";
        my $difflag = $value{"difflags"};
        system("tcsh -c \"diff $difflag $f proto/$filename >& .status\"");
        io_failure($premsg.$f.$postmsg) if (-f ".status" && `wc -c .status | cut -f1 -d' '` != 0);
        system("rm -f .status");            
    }
} 

sub dos2unix {
    my $f = shift;
    my $filename = shift;
    system("tr -d '\015' < $f > /tmp/$filename.$$; mv /tmp/$filename.$$ $f");
}

sub compare {
    compare_low("Differences found in file ", "");
}

sub proto {
    my @args = @_;
    my $srcdir = $test_srcdir . "/";
    $srcdir = "../".$srcdir if ($srcdir !~ /^\//);
    my $qcr;
    if (!(-d "proto")) {
        mkdir("proto") || io_failure($!);
    }
    open(FILLPROTO, "> fill_proto.sh") || return io_failure("Failed to prepare comparison reference files: proto/{"."@args"."}");
    print FILLPROTO "set genstatus = 0 \n";
    print FILLPROTO "set destdir = \"`pwd`\"/proto \n";
    print FILLPROTO "set cmpfiles = \"`pwd`\"/.cmpfiles \n";
    print FILLPROTO "rm -rf \"\$cmpfiles\" >& /dev/zero \n";
    print FILLPROTO "foreach f ("."@args".") \n";
    print FILLPROTO "  echo \$f >> \"\$cmpfiles\" \n";
    print FILLPROTO "  if (-f \$f) then \n";
    print FILLPROTO "    mv -f \$f \"\$destdir/\" >>& .status \n";
    print FILLPROTO "  else \n";
    print FILLPROTO "    cp -f \"".$srcdir."\"/\$f \"\$destdir/\" >>& .status \n";
    print FILLPROTO "  endif \n";
    print FILLPROTO "  if (\$status != 0) set genstatus = \$status \n";
    print FILLPROTO "end\n";
    print FILLPROTO "rm -rf "."@args"." >& /dev/zero \n";
    print FILLPROTO "exit(\$genstatus)\n";
    close(FILLPROTO);
    open(STATUS, "> .status");
    close(STATUS);
    my $protocol = `tcsh -f fill_proto.sh`;
    open(STATUS, "< .status") || return io_failure("An error occurred while preparing comparison reference files: proto/{"."@args"."}");
    $protocol = $protocol.$_ while(<STATUS>);
    close(STATUS);
    open(CMPFILES, "< .cmpfiles");
    my @cmpfiles = ();
    while(<CMPFILES>) {
        s/\n//g;
        push(@cmpfiles, $_);
    }
    close(CMPFILES);
    push(@files_to_compare, join("#", @cmpfiles));
    `rm -f .status .cmpfiles`;
    $DBG && print "Files to compare: "."@cmpfiles"."\n";
    io_failure($protocol) if (length($protocol) > 0);
}

sub parse_set_command {
    my @args = @_;
    my $variable = "";
    my $instr = shift(@args);
    my $first = shift(@args);
    my $append = 0;

    if ($first =~ /(.*)=(.*)/ || $first =~ /(.*)\+=(.*)/) {
        $variable = $1;
        @args = ($2, @args) if (length($2) > 0);
        $append = ($first =~ /(.*)\+=(.*)/);
    }
    else {
        my $second = shift(@args);
        if ($second =~ /^=(.*)/ || $second =~ /(.*)\+=(.*)/) {
            $variable = $first;
            @args = ($1, @args) if (length($1) > 0);
            $append = ($second =~ /(.*)\+=(.*)/);
        }
    }

    @args = ($value{$variable}, @args) if ($append);
    return ($variable, @args) if (length($variable) != 0);
    io_failure("Wrong format in ".$instr." instruction"); 
    return ();
}

sub set_value {
    my @result = parse_set_command("set", @_);
    return if (@result == 0);
    my $variable_ = shift(@result);
    $value{$variable_} = "@result";
}

sub set_eval {
    my @result = parse_set_command("eval", @_);
    return if (@result == 0);
    my $variable_ = shift(@result);
    my $command = join(' ', @result);
    $value{$variable_} = `$command`;
    $value{$variable_} =~ s/\s+$//; 
}

sub run_spec_instr {
    my @args = split(/\s+/, "@_");
    my $command = shift(@args);
    $command =~ s/^\@//;
    my %dispatcher = ("rvt" => \&run_rvt,
                      "compare" => \&compare,
                      "proto" => \&proto,
                      "set" => \&set_value,
                      "eval" => \&set_eval 
                     );
    my $aaa = $dispatcher{$command};
    $aaa->(@args);
}

sub test_failed {
    my $name = shift;
    $cur_test_failed = 1;
    print "Test " . $name . " failed: " . "@_" . "\n";
    push(@failed_tests, $name);
    return $name;
}

sub io_failure {
    my($filename, $dir) = fileparse(getcwd());
    return test_failed($filename, @_);
}

sub create_fail_log {
    chdir($value{"run_dir"});
    `rm -f fail.log`;
    return if (@_ == 0);
    my @failed = ();
    my $prev = "";
    foreach my $a (@_) {
        if ($a ne $prev) {
            push @failed, $a;
            $prev = $a;
        }
    }
    open(FAIL_LOG, "> fail.log");
    print FAIL_LOG "@failed";
    close(FAIL_LOG);
    print "\"".$value{"run_dir"}."/fail.log\" dumped.\n";
}

sub update_instructions {
    my @res = ();
    my $instr;

    foreach $instr (@_) {
        if ($instr =~ /^\@compare\s+\S+/) {
            my $proto_instr = $instr;
            $proto_instr =~ s/^\@compare/\@proto/g;
            @res = ($proto_instr, @res);
        }        
        push(@res, $instr);
    }

    return @res;
}

sub get_test_names {
    my $conf = shift;
    my %tests = ();
    if (@_ == 0) {
        open(INCONF, "< " . "$conf") || die "File ".$conf." not found\n";
        while(<INCONF>) {
            if (/^\@test/) {
                my @testinstr = split(/\s+/, $_);
                $tests{$testinstr[1]} = $testinstr[1];
            }
        }
        close(INCONF);
    } else {
        my $listfile = shift;
        open(FAILLOG, "< ".$listfile) || die "Could not locate the list of the tests to run (".$listfile.")\n";
        while(<FAILLOG>) {
            foreach my $test (split(/\s+/, $_)) {
                $tests{$test} = $test;
            }
        }
        close(FAILLOG);
    }
    return %tests;
}

sub parse_command_line_options {
    while (@_ > 0) {
        my $option = shift;
        if ($option            if ($option == '-args') {
                my $add_args = shift;
                $value{"global_rvt_args"} .= $add_args." ";
                print "Additional options ".$add_args." will be enforced on the tests.\n";
            }
            elsif ($option == '--') {
                return @_;
            }
            elsif ($option =~ /-h(elp)?/) {
                print_help_and_exit();
            }
            else {
                print "Illegal option ".$option."\n"; 
                print_help_and_exit(); 
            } 
           
        } 
        else {
            unshift(@_, $option);
            return @_;
        }
    }
    return @_;
}

sub print_help_and_exit {
    die <<EOF
Usage: $0 rvt_file [-args "rvt_options"] [tests_file]

  Where: rvt_file is the path to rvt.exe to be tested
         rvt_options are options (separated with space characters) with which
                     RVT will be run in addition to specific per-test options.
         tests_file is the path to the list of the names of the tests to run
EOF
;
}

sub ctrl_C {
    my @failed_or_not_run = (@failed_tests, keys %torun);
    print "Ctrl-C interruption. Attempting to dump fail.log... \n";
    create_fail_log(@failed_or_not_run);
    exit(1);
}
