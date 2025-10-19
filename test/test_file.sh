#!/bin/bash

MINISHELL="../minishell"

# args:
#	$1 = comando a ejecutar, string
#	$2 = comando opcional, salida esperada
run_one_test() {
	local test_str="$1"
	local expected="$2"
	local out_usr
	local out_bash
	local status_usr
	local status_bash

	# Ejecutar test
	out_usr=$(printf "%s\necho \$?\nexit\n" "$test_str" | "$MINISHELL" 2>&1)
	out_usr=$(echo "$out_usr" | grep -v '^minishell-')
	status_usr=$(echo "$out_usr" | tail -n 1)
	out_usr=$(echo "$out_usr" | sed '$d')
	out_bash=$(printf "%s\necho \$?\nexit\n" "$test_str" | bash 2>&1)
	status_bash=$(echo "$out_bash" | tail -n 1)
	out_bash=$(echo "$out_bash" | sed '$d')

	if [ -n "$expected" ]; then
		out_bash="$expected"
	fi
	
	# Compare
	if [[ "$out_usr" == "$out_bash" ]]; then
		echo "✅ [OK] test: $test_str"
	else
		echo "❌ [Salida incorrecta] test: $test_str"
		echo "    - Resultado minishell: $out_usr"
		echo "    - Resultado bash: $out_bash"
	fi
	if [ $status_usr -ne $status_bash ]; then
		echo "⚠️ [Return diferente] test: $test_str → minishell: $status_usr, bash: $status_bash"
	fi
}

# args:
#	$1 = fichero a ejecutar, string
run_tests_from_file() {
	local file="$1"
	local section_name=$(basename "$file" .txt)
	local test_str
	local expected

	echo "=== Seccion: $section_name ==="
	while IFS= read -r line; do
		# Ignorar comments o blanks
		[[ -z "$line" || "$line" =~ ^# ]] && continue

			## Si => separar comando en 2
			if [[ "$line" == *"=>"* ]]; then
				test_str="${line%%=>*}"
				expected="${line#*=>}"
				test_str=$(echo "$test_str" | xargs)
			expected=$(echo "$expected" | xargs)
			run_one_test "$test_str" "$expected"
		else
			run_one_test "$line"
		fi
	done < "$file"
	echo
}

run_tests_from_file "$1"
