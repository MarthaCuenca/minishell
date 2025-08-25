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
	- [ ] Parser 04/09/25 (M)
	- [ ] Expander 28/08/25 (M)
  
- [ ] Ejecutables: 01/09/25  (F)
	- [ ] Ejecutar ejecutable
	- [ ] Pipex: | (Info interesante: [link](https://www.cs.toronto.edu/~rupert/209/lec09.pdf))
	- [ ] Redirecciones: <, <<, >, >>
   
- [ ] Built-ins:
	- [ ] ctrl-C, ctrl-D, ctrl-\
	- [ ] echo
	- [ ] cd
	- [ ] pwd
	- [ ] export
	- [ ] unset
	- [ ] env
	- [ ] exit
   
 - [ ] HEREDOC
 - [ ] Gestor de señales 08/09/25 (F)
 - [ ] Historial (11/09/25)

- [ ] TESTS (extra)


## Casos extra

- ls | > hola
- > hola | ls
