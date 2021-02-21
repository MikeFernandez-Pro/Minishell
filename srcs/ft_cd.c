/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 14:07:00 by user42            #+#    #+#             */
/*   Updated: 2020/09/09 12:09:20 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_check_errors_cd2(t_args *args)
{
	char	cwd[1024];

	if (ft_strncmp(args->str, ".", ft_strlen(args->str)) == 0)
	{
		if (!(getcwd(cwd, 1024)))
		{
			ft_putstr_fd("\033[1;31mcd : erreur de détermination du répertoire \
			actuel : getcwd : ne peut accéder aux répertoires parents : Aucun \
			fichier ou dossier de ce type\n\033[0;0m", 2);
			return (1);
		}
		return (0);
	}
	if (ft_check_size_args_cd(args) != 0)
		return (1);
	return (2);
}

int		ft_change_cd(t_args *args, t_env *env_cpy, t_gbl *gbl, char *cwd)
{
	if (ft_strncmp(args->str, "$dir", 4) == 0)
	{
		ft_strdel(&args->str);
		args->str = ft_strdup(ft_getenv("HOME", gbl->env));
	}
	getcwd(cwd, sizeof(cwd));
	if (chdir(args->str) != 0)
	{
		ft_putstr_fd(ERROR_FF, 2);
		return (1);
	}
	while (env_cpy && env_cpy->var
	&& ft_strncmp(env_cpy->var, "OLDPWD=", 7) != 0)
		env_cpy = env_cpy->next;
	if (env_cpy)
	{
		ft_strdel(&env_cpy->valeur);
		env_cpy->valeur = ft_strdup(ft_getenv("PWD", gbl->env));
	}
	else
		add_back_env(&gbl->env, ft_strdup("OLDPWD="),
		ft_strdup(ft_getenv("PWD", gbl->env)), gbl);
	ft_change_pwd(gbl);
	return (0);
}

char	*ft_change_by_home(t_env *env, char *str)
{
	t_env	*first_env;
	char	*cpy;
	char	*cpy2;

	cpy2 = NULL;
	first_env = env;
	while (env)
	{
		if (strncmp(env->var, "HOME=", ft_strlen(env->var)) == 0)
		{
			cpy = ft_strdup(&str[1]);
			cpy2 = ft_strdup(env->valeur);
			cpy2 = ft_strjoin_free(cpy2, cpy, 3);
			ft_strdel(&str);
			break ;
		}
		env = env->next;
	}
	env = first_env;
	return (cpy2);
}

void	ft_check_path(t_env *env, t_gbl *gbl)
{
	t_env *first_env;

	first_env = env;
	while (env && env->var
	&& ft_strncmp(env->var, "PATH=", 7) != 0)
		env = env->next;
	if (!env)
		add_back_env(&gbl->env, ft_strdup("PATH="),
		ft_strdup(gbl->path), gbl);
	env = first_env;
}

int		ft_cd(t_args *args, t_gbl *gbl)
{
	t_env	*env_cpy;
	char	cwd[1024];
	int		ret;

	env_cpy = gbl->env;
	ft_check_path(env_cpy, gbl);
	if (!args || !args->str
	|| ft_strncmp(args->str, "~", ft_strlen(args->str)) == 0)
		return (ft_check_cd_errors(gbl->env));
	if (args->str[0] == '~')
		args->str = ft_change_by_home(gbl->env, args->str);
	if ((ret = ft_check_errors_cd2(args)) != 2)
		return (ret);
	if (ft_strncmp(args->str, "-", 1) == 0)
		return (ft_oldpwd(gbl));
	if ((ret = ft_change_cd(args, env_cpy, gbl, cwd)) == 1)
		return (1);
	return (0);
}
