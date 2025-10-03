# Minishell

## TODO:

- [x] Variables de entorno: 
	- [x] Recolectar las variables del shell anterior v3 (t_list)

- [ ] Recibir input, interpretar-lo, almacenar-lo: 10/07/25 (M)
	- [x] Lexer 
		- [x] Uso de readline y hacer free
 		- [x] Struct token
   		- [x] Gestion comillas dobles y comillas simples
     		- [x] Simbolo dolar
	- [x] Parser 04/09/25 (M)
	- [x] Expander
  
- [ ] Ejecutables: 01/09/25  (F)
	- [x] Ejecutar ejecutable
	- [x] Pipex: | (Info interesante: [link](https://www.cs.toronto.edu/~rupert/209/lec09.pdf))
	- [x] Redirecciones: <, <<, >, >>
   
- [ ] Built-ins:
	- [ ] ctrl-C, ctrl-D, ctrl-\
	- [x] echo
	- [x] cd
	- [x] pwd
	- [x] export
	- [x] unset
	- [x] env
	- [x] exit
   
 - [x] HEREDOC
 - [ ] Gestor de señales 08/09/25 (F)
 - [x] Historial (11/09/25)

- [ ] TESTS (extra)


## Casos extra
- cat | cat | ls
