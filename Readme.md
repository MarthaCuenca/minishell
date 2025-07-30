# Minishell

## TODO:

- [ ] Variables de entorno: 20/07/25 (M)
	- [x] Recolectar las variables del shell anterior v3 (t_list)

- [ ] Recibir input, interpretar-lo, almacenar-lo: 10/07/25 (M)
	- [x] Lexer 30/07/25 (M)
		- [x] Uso de readline y hacer free
 		- [x] Struct token
   		- [x] Gestion comillas dobles y comillas simples
     		- [x] Simbolo dolar
	- [ ] Parser 03/08/25 (M)
	- [ ] Expander 10/08/25 (M)
  
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
 - [ ] Gestor de señales 05/08/25 (F)
 - [ ] Historial
