# Minishell

## TODO:

- [ ] Variables de entorno: 20/07/25 (M)
	- [x] Recolectar las variables del shell anterior v3 (t_list)

- [ ] Recibir input, interpretar-lo, almacenar-lo: 10/07/25 (M)
	- [ ] Lexer 25/07/25 (M)
		- [x] Uso de readline y hacer free
 		- [ ] Struct token
   		- [x] Gestion comillas dobles y comillas simples
     		- [ ] Simbolo dolar
	- [ ] Parser 03/07/25 (M)
	- [ ] Expander 10/07/25 (M)
  
- [ ] Ejecutables: 31/07/25 (F)
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
 - [ ] Gestor de señales 05/07/25 (F)
 - [ ] Historial
