/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <moel-gha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 16:45:32 by lissam            #+#    #+#             */
/*   Updated: 2024/05/28 10:09:38 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

typedef enum types
{
	STRING,
	REDIRECT_INPUT,
	REDIRECT_APPEND,
	REDIRECT_OUTPUT,
	PIPE,
	HEREDOC,
	WHITE_SPACE,
	ERROR,
}								t_types;

typedef struct files_redirections
{
	char						*file;
	t_types						type;
	int							qouted;
	char						*limiter;
	struct files_redirections	*next;
}								t_files_redirections;

typedef struct cmd
{
	char						*cmd;
	char						**args;
	t_files_redirections		*files;
	struct cmd					*next;
	int							processindex;
}								t_cmd;

typedef struct prompt_nodes
{
	char						*string;
	t_types						type;
	struct prompt_nodes			*next;

}								t_prompt_nodes;

typedef struct s_env
{
	char						*key;
	char						*value;
	int							status;
	struct s_env				*next;
}								t_env;

typedef struct expand_norms
{
	t_prompt_nodes				*tmp;
	int							i;
	int							j;
	int							k;
	char						*str;
	char						*value;
	char						*tmp_str;
	char						*freestr;
	t_env						*tmp_env;
	char						*tmpvalue;
}								t_expand_norms;

typedef struct get_cmd_norms
{
	t_cmd						*cmds;
	t_cmd						*tmpcmds;
	t_files_redirections		*tmpfiles;
	t_prompt_nodes				*tmp;
	char						*str;
	char						*tmpstr;
	char						*free_str;
	int							index;
	char						*tty;
	char						*pindex;
	char						*tmpfile;
}								t_norms_get_cmd;

typedef struct herdoc_exp_v_norms
{
	int							i;
	int							j;
	int							k;
	char						*str;
	t_env						*tmp_env;
	char						*free_str;
	char						*value;
	char						*tmp_str;
	char						*tmp_value;
}								t_herdocexp_v;

typedef struct remover_norms
{
	int							i;
	int							j;
	char						*tmp_str;
	char						*empty;
	char						*substr;
}								t_remover_norms;

typedef struct qoutes_remover_norms
{
	t_cmd						*tmp_cmd;
	int							i;
	char						*str;
	t_files_redirections		*fl;
}								t_q_r_n;

extern t_env					*g_lobal_env;
void							free_files(t_files_redirections *files);
void							free_args(char **args);
t_cmd							*lexer(char *prompt);
t_cmd							*actions(t_prompt_nodes *p);
void							skip_first_spaces(char *prompt, int *i);
void							print_errors_dup(char *str,
									t_prompt_nodes *prompt_nodes);
void							print_errors_token(char *str);
void							free_prompt_nodes(t_prompt_nodes *node);
void							free_prompt_nodes(t_prompt_nodes *node);
int								check_spaces(char *str);
void							run_builtin(t_cmd *built);
void							start_execution(t_cmd *prompt);
void							ft_echo(t_cmd *all);
void							ft_env(t_env *my_env);
int								isexistenv(t_env *env, char *key);
void							ft_exit(t_cmd *head);
void							success(void);
void							ft_pwd(void);
void							ft_execute(t_cmd *e);
void							ft_execute2(t_cmd *ex, int tmpout, int tmpint,
									int fd);
void							ft_cd(t_cmd *path, t_env *my_env);
void							ft_export(t_cmd *head);
void							add_or_update_env(t_env **global_env, char *key,
									char *value);
void							ft_unset(t_cmd *head);
void							show_export(t_env *head);
void							bubble_sort_env(t_env *head);
int								check_parexport(char *str);
int								start_std(t_cmd *args);
void							append_value_env(t_env **g_env, char *variable,
									char *valueapp);
t_env							*new_env_node(char *key, char *value);
void							display_nodes(t_env *my_env);
void							ft_add_env_back(t_env **lst, t_env *new);
void							update_env_value(t_env *my_env, char *key,
									char *value);
t_prompt_nodes					*lst_new2(char *str, t_types t);
void							ft_lstadd_back2(t_prompt_nodes **lst,
									t_prompt_nodes *new);
void							split_chars(int *i, char *prompt,
									t_prompt_nodes **prompt_nodes);
int								split_output_redirection(int *i, char *prompt,
									t_prompt_nodes **prompt_nodes);
void							skip_spaces(char *prompt, int *i,
									t_prompt_nodes **prompt_nodes);
int								split_input_redirection(int *i, char *prompt,
									t_prompt_nodes **prompt_nodes);
int								split_pipe(int *i, char *prompt,
									t_prompt_nodes **prompt_nodes);
int								split_double_quotes(int *i, char *prompt,
									t_prompt_nodes **prompt_nodes);
int								split_single_quote(int *i, char *prompt,
									t_prompt_nodes **prompt_nodes);
void							add_to_prompt_nodes(char *str,
									t_prompt_nodes **prompt_nodes,
									t_types type);
int								syntax_error(t_prompt_nodes *prompt_nodes);
void							print_errors_token(char *str);
void							print_errors_dup(char *str,
									t_prompt_nodes *prompt_nodes);
int								is_builtin(char *cmd);
t_cmd							*get_cmds(t_prompt_nodes *p);
void							redirection_input(t_norms_get_cmd *gcmd_v);
void							redirection_output(t_norms_get_cmd *gcmd_v);
void							redirection_append(t_norms_get_cmd *gcmd_v);
void							free__null(t_norms_get_cmd *gcmd_v);
void							herdoc(t_norms_get_cmd *gcmd_v);
char							*correcttty(char *ttyname);
void							take_cmds(t_norms_get_cmd *gcmd_v);
t_cmd							*lst_new3(void);
void							set_null(t_norms_get_cmd *gcmd_v);
void							check_types(t_norms_get_cmd *gcmd_v);
void							ft_lstadd_back3(t_cmd **node, t_cmd *new);
t_files_redirections			*lst_new4(void);
void							ft_lstadd_back4(t_files_redirections **node,
									t_files_redirections *new);
void							init_get_cmd_variables(t_norms_get_cmd *gcmd_v);
char							**ft_split2(char const *s, char c);
void							skip_inside_qoutes(char const *s, int *i);
void							get_word_with_qoutes(char const *s, int *i);
void							expanding(t_prompt_nodes *p);
void							start_expand(t_expand_norms *exp_v);
void							get_exit_status(t_expand_norms *exp_v);
void							get_value(t_expand_norms *exp_v);
void							take_string_after_dolar(t_expand_norms *exp_v);
void							initexpand_vars(t_expand_norms *exp_v);
void							herdoc_case(t_expand_norms *exp_v);
void							get_env_variable(t_expand_norms *exp_v);
void							count_dolars(t_expand_norms *exp_v);
void							get_none_variables(t_expand_norms *exp_v);
void							join_odd_dolars(t_expand_norms *exp_v);
void							odd_number_dolar(t_expand_norms *exp_v);
void							has_question_mark(t_expand_norms *exp_v);
void							take_values(t_expand_norms *exp_v);
void							even_number_dolar(t_expand_norms *exp_v);
void							quotes_remover(t_cmd *cmd);
void							get_inside_single(t_remover_norms *remover_n,
									char *str);
void							get_inside_double(t_remover_norms *remover_n,
									char *str);
void							init_remover_vars(t_remover_norms *remover_n);
void							init_qoutes_remover_variables(t_q_r_n *q_r,
									t_cmd *cmd);
void							qouted_files(t_q_r_n *q_r);
void							qouted_args(t_q_r_n *q_r);
char							*remover(char *str);
void							restore_fd(int tmpout, int tmpint);
char							**env_to_array(t_env *env);
int								env_list_size(t_env *env);
void							change_shlvl(t_env *global_env);
void							run_cmd(t_cmd *cmd);
char							*get_path(char *cmd, char **env);
void							ft_free_all(char **f);
char							*get_env(char *name, char **env);
char							*get_exec_path(char *path, char *cmd);
t_env							*convert_env(char **en);
t_env							*behavior_env(void);
char							**split_first_equal(char *str);
char							**allocate_key_value(const char *str,
									const char *equal_pos);
void							free_split_result(char **split_result);
void							ft_pipe(t_cmd *cmd);
int								stdin_stdout(t_cmd *std, int *tmpout,
									int *tmpint);
void							set_status(int status);
int								check_stdout(t_files_redirections *files);
int								check_stdin(t_files_redirections *files);
void							run_stdout(t_files_redirections *files);
void							run_stdin(t_files_redirections *files);
int								count_heredoc(t_cmd *hrdc);
int								ambiguous(t_cmd *ambig);
int								check_pipe(t_cmd *pi);
void							ft_herdoc(t_cmd *tmprmpt);
char							*herdoc_expander(char *herdoc_str);
void							handle_sigint(int sig);
void							handler_hd(int sig);
void							handler(int sig);
int								seaech_home(t_env *my_env);
void							wait_for_children(void);
int								check_builts(t_cmd *cmd);
void							cleanup_g_lobal_env(void);
void							cmd_not_found(char *command);
void							finalize_pipeline(t_cmd *cmd, int input_fd);
void							run_pipeline(t_cmd *cmd, int input_fd,
									int output_fd, int *fd);
void							process_command(t_cmd *cmd, int *input_fd,
									int fd[2]);
void							free_rcrs(char *path, char **env_array);
void							handle_pipe_error(void);
char							*ft_freepath(char *pat);
char							**allocate_key_value(const char *str,
									const char *equal_pos);
void							free_split_result(char **split_result);
void							ft_pipe(t_cmd *cmd);
int								stdin_stdout(t_cmd *std, int *tmpout,
									int *tmpint);
void							set_status(int status);
int								check_stdout(t_files_redirections *files);
int								check_stdin(t_files_redirections *files);
void							run_stdout(t_files_redirections *files);
void							run_stdin(t_files_redirections *files);
int								count_heredoc(t_cmd *hrdc);
int								ambiguous(t_cmd *ambig);
int								check_pipe(t_cmd *pi);
void							ft_herdoc(t_cmd *tmprmpt);
char							*herdoc_expander(char *herdoc_str);
void							init_variables_hexp(t_herdocexp_v *hev);
void							even_dolars(t_herdocexp_v *hev,
									char *herdoc_str);
void							odd_dolars(t_herdocexp_v *hev,
									char *herdoc_str);
void							count_dolars_herdoc(t_herdocexp_v *hev,
									char *herdoc_str);
void							start_expanding_string(t_herdocexp_v *hev,
									char *herdoc_str);
void							actions_getting_values(t_herdocexp_v *hev,
									char *herdoc_str);
void							exit_value(t_herdocexp_v *hev);
void							get_string_value(t_herdocexp_v *hev,
									char *herdoc_str);
void							get_value_before_dolar(t_herdocexp_v *hev);
void							get_env_value(t_herdocexp_v *hev);
void							handle_sigint(int signum);
void							wait_for_children(void);
void							cleanup_g_lobal_env(void);
void							rl_replace_line(const char *text,
									int clear_undo);
#endif