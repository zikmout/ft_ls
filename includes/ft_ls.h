/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssicard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 16:41:14 by ssicard           #+#    #+#             */
/*   Updated: 2016/05/07 16:43:43 by ssicard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "../libft/libft.h"
# include "../libft/printf.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <time.h>
# include <pwd.h>
# include <errno.h>
# include <grp.h>
# define NB_FLAGS 6
# define VALID_FLAGS "lRarti"
# define F_LMIN 0
# define F_RMAJ 1
# define F_AMIN 2
# define F_RMIN 3
# define F_TMIN 4
# define F_IMIN 5
# define MIN(N, M) ((N < M) ? N : M)
# define MINOR(x) ((x) & 0xffffff)
# define MAJOR(x) (((x) >> 24) & 0xff)

typedef struct s_dat	t_data;
struct	s_dat
{
	char				*perm;
	int					n_lnk;
	char				*st_uid;
	char				*st_gid;
	int					size;
	char				*mtime;
	int					block;
	int					inode;
	long long			t_stp;
	long long			t_stp2;
	dev_t				dev;
	char				*lnk_p;
};

typedef struct s_f		t_f;
struct	s_f
{
	char				*file_n;
	t_data				*data;
	struct s_f			*next;
};

typedef struct s_env	t_env;
struct	s_env
{
	char				*flags;
	t_f					**head;
	int					first;
	int					multi_dir;
};

typedef struct s_m		t_m;
struct	s_m
{
	t_f				*cur;
	t_f				*new0;
	t_f				*new1;
	t_f				*new2;
};

/*
** utils.c
*/
int		check_flag(char c);
void	ft_usage(char c);
char	*get_fn(char *dir_name);
void	print_arg_dir(t_list **begin);
/*
** main.c
*/
void	list_files(char *dir_name);
void	list_dir(char *dir_name);
void	print(void);
char	*get_path(struct stat *sb, char *path, unsigned long ino);
char	*get_dir_n(unsigned long ino);

/*
** link_list.c
*/
int		get_total(t_f **begin);
void	print_lst(t_f **begin, t_env *e);
void	print_lst_rev(t_f *begin, t_env *e);
void	free_lst(t_f **begin);
/*
** link_list2.c
*/
void	whi(t_m *m, struct stat dp, t_env *e, DIR *d);
t_f		*ls_start_errno(t_f *head, t_env *e);
void	ls_start(t_f *head, t_env *e);
t_f		*new_elem(char *str, t_data *data);
void	push_back(t_f **begin, char *str, t_data *data);
/*
** link_list3.c
*/
t_m		*mutli_lst(void);
t_f		*mini_check(t_env *e, t_f *head, t_m *m);
t_f		*list_end(t_f *lst);
/*
** sort_list.c
*/
void	make_sort(t_f **head, t_env *e);
t_f		*split(t_f *list, t_env *e);
t_f		*merge(t_f *lg, t_f *ld, t_env *e);
t_f		*merge_rev(t_f *lg, t_f *ld, t_env *e);
void	reverse(t_f **head);
/*
** init.c
*/
void	init_s_env(t_env *e);
int		set_flags(t_env *e, char **av, int i, int k);
int		get_arg_dir(t_env *e, char **av);
int		get_arg_dir2(int i, int k, char **av, t_env *e);
/*
** try.c
*/
int		recur(char *dir_name, t_env *e);
void	recur2(t_f *head, t_env *e, struct stat dp, char *dir_name);
int		print_error(t_env *e, char *dir_name);
void	print_top_lst(t_env *e, char *dir_name);
/*
** show.c
*/
void	show_list(t_env *e, char *dir_name, t_f **head);
void	to_push(t_env *e, char *d_name, t_data *data, t_f **head);
t_data	*fill_dat2(char *d_name, struct stat dp, t_data *data);
t_data	*fill_dat(char *d_name);
/*
** data.c
*/
char	*get_perm(struct stat dp);
char	*ft_getnstr(const char *s, size_t n);
char	*get_time(struct stat *stat);
char	*get_perm2(struct stat dp, char *tab);
#endif
