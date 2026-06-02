#!/usr/bin/env bash

set -u

usage() {
	cat <<'EOF'
Usage: ./test_skyscraper.sh -s <size> [options] <binary>...

Required for tests:
  -s <size>       Test a binary compiled for <size>x<size>. Valid sizes: 4..9.

Options:
  -n <attempts>   Number of good-case attempts to run. Ignored with -e.
  -c <count>      Compare <count> binaries using the same generated cases.
  -v              Run tests through valgrind.
  -e              Only run the fixed bad input/error cases.
  -r              Run one attempt. Same as -n 1.
  -p              Print the standard solver stdout square. This is the default.
  -l              Print the square with clues laid out on their respective sides.
  -h              Show this help.

Default test counts by size:
  4x4: 20 good cases
  5x5: 10 good cases
  6x6: 10 good cases
  7x7: 10 good cases
  8x8:  5 good cases
  9x9:  5 good cases

Examples:
  ./test_skyscraper.sh -s 4 ./rush-01
  ./test_skyscraper.sh -s 6 -n 3 ./rush-01
  ./test_skyscraper.sh -s 8 -n 20 -c 2 ./rush-01 ./rush-02
  ./test_skyscraper.sh -s 4 -e -v ./rush-01
  ./test_skyscraper.sh -s 4 -r -l ./rush-01

The script does not compile your code. Build the requested size yourself first.
EOF
}

die() {
	printf 'Error: %s\n\n' "$1" >&2
	usage >&2
	exit 2
}

size=
attempts=
binary_count=1
use_valgrind=0
only_error=0
one_random=0
had_option=0
print_mode=standard

while getopts ":s:n:c:verplh" opt; do
	had_option=1
	case "$opt" in
		s) size=$OPTARG ;;
		n) attempts=$OPTARG ;;
		c) binary_count=$OPTARG ;;
		v) use_valgrind=1 ;;
		e) only_error=1 ;;
		r) one_random=1 ;;
		p) print_mode=standard ;;
		l) print_mode=layout ;;
		h)
			usage
			exit 0
			;;
		:)
			die "option -$OPTARG requires an argument"
			;;
		\?)
			die "unknown option -$OPTARG"
			;;
	esac
done
shift $((OPTIND - 1))

if [ "$had_option" -eq 0 ]; then
	usage
	exit 0
fi

case "$size" in
	4|5|6|7|8|9) ;;
	"") die "missing -s <size>" ;;
	*) die "-s must be one of: 4, 5, 6, 7, 8, 9" ;;
esac

case "$binary_count" in
	""|*[!0-9]*) die "-c must be a positive integer" ;;
	0) die "-c must be greater than 0" ;;
esac

[ $# -eq "$binary_count" ] \
	|| die "expected exactly $binary_count binary argument(s)"
binaries=("$@")

case "$attempts" in
	"") ;;
	*[!0-9]*) die "-n must be a positive integer" ;;
	0) die "-n must be greater than 0" ;;
esac

i=0
while [ "$i" -lt "$binary_count" ]; do
	binary=${binaries[$i]}
	[ -f "$binary" ] || die "binary does not exist: $binary"
	[ -x "$binary" ] || die "binary is not executable: $binary"
	i=$((i + 1))
done

if [ "$use_valgrind" -eq 1 ] && ! command -v valgrind >/dev/null 2>&1; then
	printf 'Error: valgrind was requested with -v, but valgrind was not found.\n' >&2
	exit 2
fi

case "$size" in
	4) test_count=20 ;;
	5|6|7) test_count=10 ;;
	8|9) test_count=5 ;;
esac

if [ -n "$attempts" ]; then
	test_count=$attempts
fi

if [ "$one_random" -eq 1 ]; then
	test_count=1
fi

pass=0
fail=0
tests_run=0
total_time_ms=0
i=0
while [ "$i" -lt "$binary_count" ]; do
	binary_pass[$i]=0
	binary_fail[$i]=0
	binary_time_ms[$i]=0
	i=$((i + 1))
done

now_ms() {
	if command -v perl >/dev/null 2>&1; then
		perl -MTime::HiRes=time -e 'printf "%.0f\n", time() * 1000'
	else
		date +%s | awk '{ print $1 * 1000 }'
	fi
}

format_ms() {
	awk -v ms="$1" 'BEGIN { printf "%.3fs", ms / 1000 }'
}

run_program() {
	local binary=$1
	local arg=$2
	local stdout_file=$3
	local stderr_file=$4
	local status_file=$5
	local status
	local vg_file

	if [ "$use_valgrind" -eq 1 ]; then
		vg_file="${stderr_file}.valgrind"
		valgrind --leak-check=full --error-exitcode=42 --log-file="$vg_file" \
			"$binary" "$arg" >"$stdout_file" 2>"$stderr_file"
		if [ -s "$vg_file" ]; then
			printf '\n[valgrind]\n' >>"$stderr_file"
			cat "$vg_file" >>"$stderr_file"
		fi
		rm -f "$vg_file"
	else
		"$binary" "$arg" >"$stdout_file" 2>"$stderr_file"
	fi
	status=$?
	printf '%s\n' "$status" >"$status_file"
}

make_good_case() {
	awk -v n="$size" -v seed="$RANDOM$RANDOM" '
	function shuffle(a,    i,j,t) {
		for (i = n; i > 1; i--) {
			j = int(rand() * i) + 1
			t = a[i]
			a[i] = a[j]
			a[j] = t
		}
	}
	function visible_line(line,    i,tallest,count) {
		tallest = 0
		count = 0
		for (i = 1; i <= n; i++) {
			if (line[i] > tallest) {
				tallest = line[i]
				count++
			}
		}
		return count
	}
	BEGIN {
		srand(seed)
		for (i = 1; i <= n; i++) {
			rows[i] = i
			cols[i] = i
			nums[i] = i
		}
		shuffle(rows)
		shuffle(cols)
		shuffle(nums)
		for (r = 1; r <= n; r++) {
			for (c = 1; c <= n; c++) {
				board[r,c] = nums[((rows[r] + cols[c] - 2) % n) + 1]
			}
		}
		out = ""
		for (c = 1; c <= n; c++) {
			for (r = 1; r <= n; r++)
				line[r] = board[r,c]
			out = out visible_line(line) " "
		}
		for (c = 1; c <= n; c++) {
			for (r = 1; r <= n; r++)
				line[r] = board[n - r + 1,c]
			out = out visible_line(line) " "
		}
		for (r = 1; r <= n; r++) {
			for (c = 1; c <= n; c++)
				line[c] = board[r,c]
			out = out visible_line(line) " "
		}
		for (r = 1; r <= n; r++) {
			for (c = 1; c <= n; c++)
				line[c] = board[r,n - c + 1]
			out = out visible_line(line) " "
		}
		sub(/ $/, "", out)
		print out
	}'
}

validate_solution() {
	local clues=$1
	local output_file=$2
	awk -v n="$size" -v clues="$clues" '
	function visible(arr,    i,tallest,count) {
		tallest = 0
		count = 0
		for (i = 1; i <= n; i++) {
			if (arr[i] > tallest) {
				tallest = arr[i]
				count++
			}
		}
		return count
	}
	BEGIN {
		clue_count = split(clues, clue, " ")
		if (clue_count != 4 * n)
			exit 1
	}
	{
		if (NF != n)
			exit 1
		if (NR > n)
			exit 1
		for (c = 1; c <= n; c++) {
			if ($c !~ /^[1-9]$/ || $c < 1 || $c > n)
				exit 1
			board[NR,c] = $c
		}
	}
	END {
		if (NR != n)
			exit 1
		for (r = 1; r <= n; r++) {
			delete seen
			for (c = 1; c <= n; c++) {
				if (seen[board[r,c]])
					exit 1
				seen[board[r,c]] = 1
			}
		}
		for (c = 1; c <= n; c++) {
			delete seen
			for (r = 1; r <= n; r++) {
				if (seen[board[r,c]])
					exit 1
				seen[board[r,c]] = 1
			}
		}
		for (c = 1; c <= n; c++) {
			for (r = 1; r <= n; r++)
				line[r] = board[r,c]
			if (visible(line) != clue[c])
				exit 1
			for (r = 1; r <= n; r++)
				line[r] = board[n - r + 1,c]
			if (visible(line) != clue[n + c])
				exit 1
		}
		for (r = 1; r <= n; r++) {
			for (c = 1; c <= n; c++)
				line[c] = board[r,c]
			if (visible(line) != clue[2 * n + r])
				exit 1
			for (c = 1; c <= n; c++)
				line[c] = board[r,n - c + 1]
			if (visible(line) != clue[3 * n + r])
				exit 1
		}
	}
	' "$output_file"
}

print_layout() {
	local arg=$1
	local stdout_file=$2
	local -a clues rows
	local border=
	local cell_width
	local i
	local row
	local row_count=0

	read -r -a clues <<<"$arg"
	if [ "${#clues[@]}" -ne "$((4 * size))" ]; then
		printf '  layout: <unavailable>\n'
		return
	fi
	while IFS= read -r row; do
		rows[$row_count]=$row
		row_count=$((row_count + 1))
	done <"$stdout_file"
	cell_width=$((2 * size - 1))
	i=0
	while [ "$i" -lt "$cell_width" ]; do
		border="${border}-"
		i=$((i + 1))
	done
	printf '  layout:\n'
	printf '      '
	i=0
	while [ "$i" -lt "$size" ]; do
		printf '%s ' "${clues[$i]}"
		i=$((i + 1))
	done
	printf '\n'
	printf '    +-%s-+\n' "$border"
	i=0
	while [ "$i" -lt "$size" ]; do
		printf '  %s | %-*s | %s\n' \
			"${clues[$((2 * size + i))]}" "$cell_width" "${rows[$i]-}" \
			"${clues[$((3 * size + i))]}"
		i=$((i + 1))
	done
	printf '    +-%s-+\n' "$border"
	printf '      '
	i=0
	while [ "$i" -lt "$size" ]; do
		printf '%s ' "${clues[$((size + i))]}"
		i=$((i + 1))
	done
	printf '\n'
}

record_result() {
	local binary_index=$1
	local name=$2
	local ok=$3
	local status=$4
	local stdout_file=$5
	local stderr_file=$6
	local duration_ms=$7
	local arg=$8
	local duration

	tests_run=$((tests_run + 1))
	total_time_ms=$((total_time_ms + duration_ms))
	binary_time_ms[$binary_index]=$((binary_time_ms[$binary_index] + duration_ms))
	duration=$(format_ms "$duration_ms")
	if [ "$ok" -eq 1 ]; then
		pass=$((pass + 1))
		binary_pass[$binary_index]=$((binary_pass[$binary_index] + 1))
		printf 'ok   %s (%s)\n' "$name" "$duration"
	else
		fail=$((fail + 1))
		binary_fail[$binary_index]=$((binary_fail[$binary_index] + 1))
		printf 'FAIL %s (%s, exit %s)\n' "$name" "$duration" "$status"
	fi
	printf '  arg:    %s\n' "$arg"
	if [ "$print_mode" = layout ]; then
		print_layout "$arg" "$stdout_file"
	else
		printf '  stdout:\n'
		if [ -s "$stdout_file" ]; then
			sed 's/^/    /' "$stdout_file"
		else
			printf '    <empty>\n'
		fi
	fi
	if [ "$ok" -eq 0 ]; then
		printf '  stderr: '
		tr '\n' ' ' <"$stderr_file"
		printf '\n'
	fi
}

run_good_test() {
	local index=$1
	local binary_index binary
	local arg stdout_file stderr_file status_file status ok start_ms end_ms duration_ms

	printf 'generating square %sx%s #%d\n' "$size" "$size" "$index" >&2
	arg=$(make_good_case)
	binary_index=0
	while [ "$binary_index" -lt "$binary_count" ]; do
		binary=${binaries[$binary_index]}
		printf 'testing %s with square %sx%s #%d\n' \
			"$binary" "$size" "$size" "$index" >&2
		stdout_file=$(mktemp)
		stderr_file=$(mktemp)
		status_file=$(mktemp)
		start_ms=$(now_ms)
		run_program "$binary" "$arg" "$stdout_file" "$stderr_file" "$status_file"
		end_ms=$(now_ms)
		duration_ms=$((end_ms - start_ms))
		if [ "$duration_ms" -lt 0 ]; then
			duration_ms=0
		fi
		status=$(cat "$status_file")
		ok=0
		if [ "$status" -eq 0 ] && validate_solution "$arg" "$stdout_file"; then
			ok=1
		fi
		record_result "$binary_index" "$binary good ${size}x${size} #$index" \
			"$ok" "$status" "$stdout_file" "$stderr_file" "$duration_ms" "$arg"
		rm -f "$stdout_file" "$stderr_file" "$status_file"
		binary_index=$((binary_index + 1))
	done
}

repeat_num() {
	local value=$1
	local count=$2
	local out=
	local i=0

	while [ "$i" -lt "$count" ]; do
		if [ -n "$out" ]; then
			out="$out "
		fi
		out="$out$value"
		i=$((i + 1))
	done
	printf '%s\n' "$out"
}

bad_cases() {
	local valid

	printf 'generating square %sx%s for error cases\n' "$size" "$size" >&2
	valid=$(make_good_case)
	printf 'testing binary with generated error cases\n' >&2
	printf '%s\n' ""
	printf '%s\n' "1 2 3"
	printf '%s\n' "$valid "
	printf '%s\n' "0 ${valid#* }"
	printf '%s\n' "$(repeat_num "$((size + 1))" "$((4 * size))")"
	printf '%s\n' "${valid/ /  }"
	printf '%s\n' "a${valid#?}"
}

run_bad_test() {
	local index=$1
	local arg=$2
	local binary_index binary
	local stdout_file stderr_file status_file status ok start_ms end_ms duration_ms

	binary_index=0
	while [ "$binary_index" -lt "$binary_count" ]; do
		binary=${binaries[$binary_index]}
		stdout_file=$(mktemp)
		stderr_file=$(mktemp)
		status_file=$(mktemp)
		start_ms=$(now_ms)
		run_program "$binary" "$arg" "$stdout_file" "$stderr_file" "$status_file"
		end_ms=$(now_ms)
		duration_ms=$((end_ms - start_ms))
		if [ "$duration_ms" -lt 0 ]; then
			duration_ms=0
		fi
		status=$(cat "$status_file")
		ok=0
		if [ "$status" -eq 1 ] && grep -qx 'Error' "$stderr_file"; then
			ok=1
		fi
		record_result "$binary_index" "$binary bad ${size}x${size} #$index" \
			"$ok" "$status" "$stdout_file" "$stderr_file" "$duration_ms" "$arg"
		rm -f "$stdout_file" "$stderr_file" "$status_file"
		binary_index=$((binary_index + 1))
	done
}

if [ "$only_error" -eq 1 ]; then
	bad_case_file=$(mktemp)
	bad_cases >"$bad_case_file"
	test_count=$(wc -l <"$bad_case_file" | tr -d ' ')
fi

printf 'Testing %d binar' "$binary_count"
if [ "$binary_count" -eq 1 ]; then
	printf 'y'
else
	printf 'ies'
fi
printf ' with size %sx%s' "$size" "$size"
if [ "$only_error" -eq 1 ]; then
	printf ' error cases'
else
	printf ' good cases'
fi
printf ' (%d attempt' "$test_count"
if [ "$test_count" -ne 1 ]; then
	printf 's'
fi
printf ')'
if [ "$use_valgrind" -eq 1 ]; then
	printf ' under valgrind'
fi
printf '\n'

if [ "$only_error" -eq 0 ]; then
	i=1
	while [ "$i" -le "$test_count" ]; do
		run_good_test "$i"
		i=$((i + 1))
	done
else
	bad_case_count=$(wc -l <"$bad_case_file" | tr -d ' ')
	i=1
	while [ "$i" -le "$test_count" ]; do
		line_number=$(( (i - 1) % bad_case_count + 1 ))
		bad_arg=$(sed -n "${line_number}p" "$bad_case_file")
		run_bad_test "$i" "$bad_arg"
		i=$((i + 1))
	done
	rm -f "$bad_case_file"
fi

if [ "$tests_run" -gt 0 ]; then
	average_time_ms=$((total_time_ms / tests_run))
	printf '\n%d passed, %d failed\n' "$pass" "$fail"
	printf 'total:   %s\n' "$(format_ms "$total_time_ms")"
	printf 'average: %s\n' "$(format_ms "$average_time_ms")"
	if [ "$binary_count" -gt 1 ]; then
		printf '\nComparison:\n'
		i=0
		while [ "$i" -lt "$binary_count" ]; do
			average_time_ms=$((binary_time_ms[$i] / test_count))
			printf '  %s: %d passed, %d failed; total %s; average %s\n' \
				"${binaries[$i]}" "${binary_pass[$i]}" "${binary_fail[$i]}" \
				"$(format_ms "${binary_time_ms[$i]}")" \
				"$(format_ms "$average_time_ms")"
			i=$((i + 1))
		done
	fi
else
	printf '\n%d passed, %d failed\n' "$pass" "$fail"
fi
[ "$fail" -eq 0 ]
