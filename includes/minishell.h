/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 22:26:26 by cbertola          #+#    #+#             */
/*   Updated: 2020/09/09 21:03:31 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <sys/wait.h>
# include <signal.h>

# define SIMPQ				39
# define DOUBQ				34
# define BACKS				92
# define MAXLONG			9223372036854775807
# define ERROR_SYNTAX "\033[1;31mErreur de syntaxe.\033[0;0m\n"
# define ERROR_DOSP "\033[1;31m .: Ceci est un dossier\033[0;0m\n"
# define ERROR_DOSS "\033[1;31m /: Ceci est un dossier\033[0;0m\n"
# define ERROR_AMB "\033[1;31mErreur de syntaxe.\033[0;0m\n"
# define ERROR_FF "\033[1;31mAucun fichier ou dossier de ce type.\033[0;0m\n"
# define ERROR_CMD "\033[1;31mLa commande est introuvable.\033[0;0m\n"
# define IDERRONE "\033[1;31mexport: identifiant non valable.\033[0;0m\n"
# define ARGUMENTS "\033[1;31mexit: trop d'arguments.\033[0;0m\n"
# define ARG_NUM "\033[1;31mexit: argument numérique nécessaire.\033[0;0m\n"
# define ACCOLADES "\033[1;31mAccolade manquante.\033[0;0m\n"
# define SUBSTITUTIONS "\033[1;31mMauvaise substitution.\033[0;0m\n"
# define DOUBLEQ "\033[1;31mDouble quote manquante.\033[0;0m\n"
# define SIMPLEQ "\033[1;31mSimple quote manquante.\033[0;0m\n"
# define OPERANDE "\033[1;31merreur de syntaxe : opérande attendu.\033[0;0m\n"
# define CROCHET "\033[1;31mCaractère incorrect entre crochets.\033[0;0m\n"
# define PARENTH "\033[1;31mParanthèse manquante.\033[0;0m\n"
# define CR_MISS "\033[1;31mCrochet manquant.\033[0;0m\n"
# define HOME "\033[1;31mbash: cd: « HOME » non défini.\033[0;0m\n"
# define CDARG "\033[1;31mbash: cd: trop d'arguments.\033[0;0m\n"
# define GETPWD "\033[1;31mpwd : Error - Failed to get pwd.\033[0;0m\n"
# define PROMPT "\033[1;33mMINISHELL ➜\033[0;0m\033[1;36m ~%s\033[0;0m$ "

typedef	struct			s_redir
{
	char				*str;
	int					ind;
	struct s_redir		*next;
}						t_redir;

typedef struct			s_args
{
	char				*str;
	struct s_args		*next;
}						t_args;

typedef struct			s_cmds
{
	char				*str;
	int					nb_args;
	t_args				*args;
}						t_cmds;

typedef struct			s_pipes
{
	char				*str;
	t_redir				*redir_in;
	t_redir				*redir_out;
	t_cmds				cmds;
	struct s_pipes		*next;
}						t_pipes;

typedef struct			s_semi
{
	char				*str;
	char				*g_line;
	int					nb_pipes;
	void				*first_semi;
	char				***all;
	t_pipes				*pipes;
	struct s_semi		*next;
}						t_semi;
typedef struct			s_env
{
	char				*var;
	char				*valeur;
	struct s_env		*next;
}						t_env;

typedef struct			s_gbl
{
	char				*path;
	char				*pwd;
	int					pid;
	int					rep;
	int					sta;
	int					error;
	int					ret;
	int					argc;
	char				*line;
	t_semi				*semi;
	t_env				*env;
}						t_gbl;

void					add_back_env(t_env **alst, char *str, char *str2,
t_gbl *gbl);
int						ft_in_quotes(char *str, int i);
t_env					*ft_tab_to_list(char **tri_selectif, t_gbl *gbl);
int						display_export(t_env *list);
char					*check_var(char *str);
char					*check_value(char *str, int i);
char					*ft_clean_spaces(char *str);
char					*ft_envcpy(char *str, t_gbl *gbl);
int						ft_find_size_arg(char *str);
char					*ft_replace_value(char *str, t_gbl *gbl);
char					*ft_replace_bashname(char *str, t_env *env);
void					lstadd_back_semi(t_gbl *gbl, char *str);
void					lstadd_back_pipes(t_gbl *gbl, t_pipes **pipes,
char *str);
void					lstadd_back_args(t_args **args, char *str, t_env *env);
int						split_semi(t_gbl *gbl);
t_pipes					*split_pipes(t_gbl *gbl, t_semi *semi);
void					cmds_args(t_cmds *cmd, char *str, t_env *env);
void					lstadd_back_redir(t_redir **redir, char *str, int i);
int						ft_isbracket(char *str, int i);
char					*ft_clean_brackets(char *str);
int						ft_verif_commands(char *str, t_gbl *gbl);
void					ft_cpy_in_squotes(char *str, char *cpy, int *i, int *j);
void					ft_cpy_in_dbquotes(char *str, char *cpy, int *i,
int *j);
int						count_pipe(t_semi *semi);
void					new_str(t_semi *semi);
void					tab_all(t_semi *semi);
void					ft_simpq_len(char *str, int *i, int *len);
int						ft_envcpylen(char *str, t_env *env);
int						ft_isbacks(char *str, int i);
int						ft_isquote(char *str, int i);
int						exec_cmds(t_semi *semi, t_gbl *gbl);
int						ft_export(t_args *args, t_gbl *gbl);
void					data_list(char *str, t_gbl *gbl);
void					ft_tri_varlst(t_env **lst_env);
int						replace_env(t_env *env, char *var, char *value);
void					suppr_maillon(t_env **list, t_env *ptr);
int						condition(char *str, char *str2);
int						ft_unset(t_args *args, t_gbl *gbl);
void					ft_free(t_semi *semi);
void					free_cmds(t_cmds *cmds);
void					free_exit(t_semi *semi, t_gbl *gbl, char *str);
void					ft_free_env(t_env *env);
char					*clean_redir(char *str, char c);
int						ft_env(t_args *args, t_gbl *gbl);
int						check_str_alpha(char *str, int len);
int						find_fcts(t_cmds *cmd, t_gbl *gbl);
int						ft_echo(t_args *args, t_gbl *gbl);
int						ft_cd(t_args *args, t_gbl *gbl);
int						ft_check_cd_errors(t_env *env);
int						ft_check_size_args_cd(t_args *args);
char					*ft_getenv(char *str, t_env *env);
int						ft_pwd(void);
int						search_mybin(char *str);
char					*check_path(char *str, t_gbl *gbl);
void					do_dup(int j, int *pipes, t_semi *semi, t_gbl *gbl);
void					wait_pipes(int nb_pipes, pid_t *pid, int *ret);
void					close_pipes(int nb_pipes, int *pipes);
void					init_pipes(int nb_pipes, int *pipes);
char					**list_to_tab(t_env *env);
int						ft_strlen_str_quotes_backs(char *s, char *str);
void					free_tab(char **tab);
void					ft_change_args(t_cmds *cmd, t_gbl *gbl);
void					ft_redir_in(char *str, t_redir **redir, t_gbl *gbl);
void					ft_redir_out(char *str, t_redir **redir, t_gbl *gbl);
void					free_exit2(t_gbl *gbl, char *str);
int						ft_exit(t_cmds *cmd, t_gbl *gbl);
void					ft_simpq_cpy_all(char *str, char *cpy, int *i, int *j);
int						ft_verif_crochets(char *str, t_env *env, t_gbl *gbl);
int						ft_iscrochet(char *str, int i);
char					*ft_replace_crochets(char *str);
void					free_exit_int(t_semi *semi, t_gbl *gbl, char *str,
int res);
int						ft_verif_paranthesis(char *str, t_gbl *gbl);
void					ft_travel_simpq(char *str, int *i);
char					*ft_replace_value2(char *str, t_gbl *gbl);
void					check_space_end(char *str, t_gbl *gbl);
int						ft_oldpwd(t_gbl *gbl);
void					ft_change_pwd(t_gbl *gbl);
void					do_fork(int j, int *pipes, t_semi *semi, t_gbl *gbl);
void					exchange_ret(t_gbl *gbl);
void					exec_fork(t_semi *semi, int j, t_gbl *gbl);
char					**new_tab(t_pipes *pipes);
void					ft_free_gbl(t_gbl *g_gbl);
void					free_exit_back_int(t_semi *semi, t_gbl *gbl,
char *str, int res);
void					exit_back2(t_gbl *gbl, char *str);
#endif
