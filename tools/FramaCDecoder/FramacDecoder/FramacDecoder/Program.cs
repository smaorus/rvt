using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;

namespace FramacDecoder
{
    class Program
    {
        static void Main(string[] args)
        {
            var lines = File.ReadAllLines(@"frama_out.txt");
            int k = -1;
            for (int i = 0; i < lines.Length; i++)
            {
                if (lines[i].StartsWith("[value] ====== VALUES COMPUTED ======"))
                {
                    k = i;
                    break;
                }
            }

            var interesting_lines =
                lines.Skip(k)
                    .Where(t => t.StartsWith("[value] Values at end of function") || t.StartsWith("   __retres ∈")).ToArray();


            var res = interesting_lines.Select((t, i) => new {t, i})
                .Where(t => t.t.Contains("__retres"))
                .Select(
                    t =>
                        new
                        {
                            fun = ExtractFuncName(interesting_lines[t.i - 1]),
                            val = ExtractFuncValues(t.t).Split(new[]{"; ", ".."}, StringSplitOptions.RemoveEmptyEntries)
                        })
                .ToArray();
            

            File.WriteAllLines(@"frama_out_parsed.txt", res.Select(t => t.fun + "|" + t.val.First() + "," + t.val.Last()));
        }

        private static string ExtractFuncValues(string t)
        {
            var res = Regex.Match(t, @"{(.+)}");
            return res.Groups[1].Value;
        }

        private static string ExtractFuncName(string line)
        {
            var res = Regex.Match(line, @"Values at end of function ([a-z]):");
            var funcName = res.Groups[1].Value;
            return funcName;
        }
    }
}
