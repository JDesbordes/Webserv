CC=clang++
CFLAGS=-Wall -Wextra -Werror -g3
NAME=libft.a
SRCS=./allocations/ft_bzero.cpp \
	 ./allocations/ft_calloc.cpp \
	 ./allocations/ft_realloc.cpp \
	 ./allocations/ft_memccpy.cpp \
	 ./allocations/ft_memchr.cpp \
	 ./allocations/ft_memcmp.cpp \
	 ./allocations/ft_memcpy.cpp \
	 ./allocations/ft_memmove.cpp \
	 ./allocations/ft_memset.cpp \
	 ./allocations/ft_strdup.cpp \
	 ./allocations/ft_free_return.cpp \
	 ./checker/ft_allisascii.cpp \
	 ./checker/ft_allisalpha.cpp \
	 ./checker/ft_allisdigit.cpp \
	 ./checker/ft_allisalnum.cpp \
	 ./checker/ft_allisprint.cpp \
	 ./checker/ft_isascii.cpp \
	 ./checker/ft_isalpha.cpp \
	 ./checker/ft_isdigit.cpp \
	 ./checker/ft_isalnum.cpp \
	 ./checker/ft_isprint.cpp \
	 ./checker/ft_strchr_chr.cpp \
	 ./checker/ft_strchr_int.cpp \
	 ./checker/ft_strrchr_chr.cpp \
	 ./checker/ft_strrchr_int.cpp \
	 ./checker/ft_min.cpp \
	 ./checker/ft_max.cpp \
	 ./converters/ft_atoi.cpp \
	 ./converters/ft_atoi_base.cpp \
	 ./converters/ft_ctos.cpp \
	 ./converters/ft_itoa.cpp \
	 ./common_functions/get_next_line.cpp \
	 ./common_functions/get_next_line_utils.cpp \
	 ./list_functions/ft_free_strs.cpp \
	 ./list_functions/ft_free_strs_tab.cpp \
	 ./list_functions/ft_lstnew_bonus.cpp \
	 ./list_functions/ft_lstadd_front_bonus.cpp \
	 ./list_functions/ft_lstsize_bonus.cpp \
	 ./list_functions/ft_lstlast_bonus.cpp \
	 ./list_functions/ft_lstadd_back_bonus.cpp \
	 ./list_functions/ft_lstdelone_bonus.cpp \
	 ./list_functions/ft_lstclear_bonus.cpp \
	 ./list_functions/ft_lstiter_bonus.cpp \
	 ./list_functions/ft_lstmap_bonus.cpp \
	 ./list_functions/ft_lstremove_if.cpp \
	 ./printers/ft_putchar_fd.cpp \
	 ./printers/ft_putstr_fd.cpp \
	 ./printers/ft_putendl_fd.cpp \
	 ./printers/ft_putnbr_fd.cpp \
	 ./printers/ft_putchar.cpp \
	 ./printers/ft_putstr.cpp \
	 ./printers/ft_putendl.cpp \
	 ./printers/ft_putnbr.cpp \
	 ./str_functions/ft_toupper.cpp \
	 ./str_functions/ft_tolower.cpp \
	 ./str_functions/ft_strlen.cpp \
	 ./str_functions/ft_strnlen.cpp \
	 ./str_functions/ft_strncmp.cpp \
	 ./str_functions/ft_strcpy.cpp \
	 ./str_functions/ft_strlcpy.cpp \
	 ./str_functions/ft_strlcat.cpp \
	 ./str_functions/ft_strnstr.cpp \
	 ./str_functions/ft_strstr.cpp \
	 ./str_functions/ft_substr.cpp \
	 ./str_functions/ft_strjoin.cpp \
	 ./str_functions/ft_strtrim.cpp \
	 ./str_functions/ft_split.cpp \
	 ./str_functions/ft_strmapi.cpp \
	 ./str_functions/ft_replace.cpp \
	 ./str_functions/ft_strfjoin.cpp \
	 ./str_functions/ft_strcmp.cpp \
	 ./str_functions/ft_count_char.cpp \
	 ./str_functions/ft_strtablen.cpp \
	 ./str_functions/ft_rm_null_tab.cpp \
	 ./btree/btree_create_node.cpp \
	 ./btree/btree_apply_prefix.cpp \
	 ./btree/btree_apply_infix.cpp \
	 ./btree/btree_apply_suffix.cpp \
	 ./btree/btree_insert_data.cpp \
	 ./btree/btree_search_item.cpp \
	 ./btree/btree_level_count.cpp \
	 ./btree/btree_apply_by_level.cpp \
	 ./btree/btree_print_util.cpp \
	 ./debug/ft_debug_str_1d.cpp \
	 ./debug/ft_debug_str_2d.cpp
OBJS=$(SRCS:.cpp=.o)
INC=libft.hpp
RM=rm -f
	
.cpp.o:
	$(CC) -I. $(CFLAGS) -c $< -o $@
all:		$(NAME)

$(OBJS):	$(INC)

$(NAME): 	$(INC) $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS) libft.ghc.h

fclean: 	clean
	$(RM) $(NAME)

re:		fclean all

.PHONY: all bonus clean fclean re
