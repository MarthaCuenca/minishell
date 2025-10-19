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
	local tmp_input_usr tmp_output_usr tmp_input_bash tmp_output_bash
	tmp_input_usr=$(mktemp)
	tmp_output_usr=$(mktemp)
	tmp_input_bash=$(mktemp)
	tmp_output_bash=$(mktemp)

	# --- Prep tmp files ---
	echo "$test_str" > "$tmp_input_usr"
	echo "exit" >> "$tmp_input_usr"

	echo "$test_str" > "$tmp_input_bash"
	echo "exit" >> "$tmp_input_bash"

	# --- Execute minishell ---
	"$MINISHELL" < "$tmp_input_usr" > "$tmp_output_usr" 2>&1
	status_usr=$?
	out_usr=$(cat "$tmp_output_usr" | grep -v '^minishell-')

	# --- Execute bash ---
	bash < "$tmp_input_bash" > "$tmp_output_bash" 2>&1
	status_bash=$?
	out_bash=$(cat "$tmp_output_bash")

	rm -f "$tmp_input_usr" "$tmp_output_usr" "$tmp_input_bash" "$tmp_output_bash" 

	# --- Compare results ---
	if [ -n "$expected" ]; then
		out_bash="$expected"
	fi

	if [[ "$out_usr" == "$out_bash" ]]; then
		echo "✅ [OK] test: $test_str"
	else
		echo "❌ [Salida incorrecta] test: $test_str"
		echo "    - Resultado minishell: $out_usr"
		echo "    - Resultado bash: $out_bash"
	fi
	if [[ "$status_usr" =~ ^[0-9]+$ && "$status_bash" =~ ^[0-9]+$ ]]; then
		if [ $status_usr -ne $status_bash ]; then
			echo "⚠️ [Return diferente] test: $test_str → minishell: $status_usr, bash: $status_bash"
		fi
	else
		echo "⚠️ Status no numerico detectado: status_usr='$status_usr', status_bash='$status_bash'"
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

run_tests_from_file "pipe_test.txt"
run_tests_from_file "builtin_test.txt"
