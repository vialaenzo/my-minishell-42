# Nom du programme
NAME = minishell

# Dossier de sortie pour les fichiers objets
OBJ_DIR = obj/
SRCS_DIR = srcs/
# Dossiers des dépendances
LIBFT_DIR = libft

# Les différentes bibliothèques
LIBFT = $(LIBFT_DIR)/libft.a

# Headers et includes
HEADER = -I./includes \
	-I./libft/includes \

# Options de compilation
CFLAGS = -Wall -Wextra -Werror
LIBS = -lreadline

# Commandes
CC = cc -g3
RM = rm -rf

# Rechercher tous les fichiers .c dans le répertoire courant
SRCS = main.c \
	builtins/ft_cd.c \
	builtins/ft_echo.c \
	builtins/ft_env.c \
	builtins/ft_exit.c \
	builtins/ft_export.c \
	builtins/ft_export_append.c \
	builtins/ft_pwd.c \
	builtins/ft_unset.c \
	exec/builtins_starter.c \
	exec/childs.c \
	exec/exec.c \
	exec/here_doc.c \
	exec/utils.c \
	exec/exec_cmds.c \
	exec/exec_cmds2.c \
	parsing/expand.c \
	parsing/fd_center.c \
	parsing/ft_cmds_args.c \
	parsing/make_cmds.c \
	parsing/make_tokens.c \
	parsing/verif_quotes.c \
	utils/debug.c \
	utils/ft_cmds.c \
	utils/ft_cmds2.c \
	utils/ft_env.c \
	utils/ft_free.c \
	utils/ft_lists.c \
	utils/ft_signals.c \
	utils/ft_tokens.c \
	utils/utils.c \
	utils/utils2.c \
	utils/utils3.c

MAKEFLAGS += --no-print-directory
TOTAL_FILES := $(words $(SRCS))
CURRENT_INDEX := 0

# Conversion des fichiers source en fichiers objets
OBJS = $(addprefix ${OBJ_DIR}, $(SRCS:.c=.o))

# Cibles
all: $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)
	@echo "\n"

# Compilation de la bibliothèque
$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(HEADER) $(LIBFT) $(LIBS)
	@echo "\n┗▷${BOLD}$(GREEN)『./$(NAME) Successfully created [✅]$(RESET)"

${OBJ_DIR}%.o: ${SRCS_DIR}%.c
	@mkdir -p $(dir $@)
	@$(eval CURRENT_INDEX=$(shell echo $$(($(CURRENT_INDEX)+1))))
	@$(eval PERCENT=$(shell echo $$(($(CURRENT_INDEX) * 100 / $(TOTAL_FILES)))))
	@printf "\r🔧 $(BLUE)$(BOLD)%3d%% $(WHITE)$(BOLD)Compiling:$(WHITE)$(BOLD) ${NAME}${RESET} $(RED)$(BOLD)%-50s $(MAGENTA)[%3d/%3d]$(RESET)" $(PERCENT) "$<" $(CURRENT_INDEX) $(TOTAL_FILES)
	@${CC} ${CFLAGS} ${HEADER} -c $< -o $@

# Nettoyage des fichiers objets
clean:
	@echo "$(BOLD) [ 🗑️ ] $(YELLOW)$(REVERSED)Cleaning up$(RESET)"
	@$(MAKE) clean -C $(LIBFT_DIR) > /dev/null 2>&1
	@$(RM) -r $(OBJ_DIR) > /dev/null 2>&1
	@echo "┗▷$(YELLOW)『$(ITALIC)./$(SRCS_DIR)'s$(RESET)$(YELLOW) object files cleaned』$(RESET)"

# Nettoyage complet
fclean: clean
	@$(MAKE) fclean -C $(LIBFT_DIR) > /dev/null 2>&1
	@$(RM) $(NAME) > /dev/null 2>&1
	@echo "┗▷$(YELLOW)『$(ITALIC)./$(NAME)'s$(RESET)$(YELLOW) cleaned』$(RESET)"

# Recompiler entièrement
re: fclean
	$(MAKE) all

test: all
	#command to generate the log file
	#valgrind --leak-check=full --track-fds=yes --trace-children=yes -s -q --gen-suppressions=all --log-file=memcheck.log ./minishell
	valgrind --leak-check=full --track-fds=yes --trace-children=yes -s -q --suppressions=valgrind_ignore.supp ./minishell

.PHONY: all clean fclean re bonus test

# ... (le reste du Makefile reste inchangé)
.SILENT:
# Colors
RED := \033[0;31m
GREEN := \033[0;32m
YELLOW := \033[0;33m
BLUE := \033[0;34m
MAGENTA := \033[0;35m
CYAN := \033[0;36m
WHITE := \033[0;37m
RESET := \033[0m
BOLD := \033[1m
UNDERLINE := \033[4m
REVERSED := \033[7m
ITALIC := \033[3m
