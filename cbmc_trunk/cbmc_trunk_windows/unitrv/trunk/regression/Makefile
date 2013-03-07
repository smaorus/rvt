default: tests.log

test:
	@./test.pl -c ../../src/unitrv

tests.log: ../test.pl
	@./test.pl -c ../../src/unitrv

show:
	@for dir in *; do \
		if [ -d "$$dir" ]; then \
			vim -o "$$dir/*.c" "$$dir/*.out"; \
		fi; \
	done;
