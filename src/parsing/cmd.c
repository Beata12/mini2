
#include "../../incl/minishell.h"

void	fill_redir_type(t_token *redir, t_token *tokarr, int *t)
{
	redir->type = tokarr[*t].type;
	(*t)++;
	if (!tokarr[*t].word)
		alloc_err();
	redir->word = ft_strdup(tokarr[*t].word);
}

void	double_redir_case(t_token *redir, t_token *tokarr, int *t)
{
	fill_redir_type(redir, tokarr, t);
	tokarr[--(*t)].type = T_RED_OUT;
}

// takes curr cmd, and token start i for this cmd
// returns token end i (where encounted pipe or end of arr)
void	fill_cmd(int cmd, int *tok, t_args *shell_data)
{
	int	a;
	int	i;
	int	o;

	a = -1;
	i = -1;
	o = -1;
	while (*tok < shell_data->tokarr_l && shell_data->tokarr[*tok].type != T_PIPE)
	{
		if (shell_data->tokarr[*tok].type == T_RED_INP
			&& spec_symb(shell_data->tokarr[*tok].word) == 2)
			double_redir_case(&shell_data->cmdarr[cmd].inp[++i], shell_data->tokarr,
				tok);
		if (shell_data->tokarr[*tok].type == T_RED_INP
			|| shell_data->tokarr[*tok].type == T_HEREDOC)
			fill_redir_type(&shell_data->cmdarr[cmd].inp[++i], shell_data->tokarr, tok);
		else if (shell_data->tokarr[*tok].type == T_RED_OUT
			|| shell_data->tokarr[*tok].type == T_APPEND)
			fill_redir_type(&shell_data->cmdarr[cmd].out[++o], shell_data->tokarr, tok);
		else
			shell_data->cmdarr[cmd].args[++a] = shell_data->tokarr[*tok].word;
		(*tok)++;
	}
}
