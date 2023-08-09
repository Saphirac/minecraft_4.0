# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gle-mini <gle-mini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/20 01:48:02 by mcourtoi          #+#    #+#              #
#    Updated: 2023/08/09 16:29:44 by gle-mini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

######################################
#              COMMANDS              #
######################################
CC					=	cc -c
LINK				=	clang
MKDIR				=	mkdir -p
RM					=	rm -rf

######################################
#             EXECUTABLE             #
######################################
NAME				=	cub3d

#######################################
#             DIRECTORIES             #
#######################################
SRC_DIR				=	src
OBJ_DIR				=	obj
INC_DIR				=	include

FT_DIR			=	libft
FT_INC_DIR		=	include
FT_INC_DIR		:=	${addprefix ${FT_DIR}/, ${FT_INC_DIR}}

MLX_DIR = mlx_linux
MLX_INC_DIR = include
MLX_INC_DIR := ${addprefix ${MLX_DIR}/, ${MLX_INC_DIR}}

#######################################
#              LIBRARIES              #
#######################################
FT_A				=	libft.a
FT_A				:=	${addprefix ${FT_DIR}/, ${FT_A}}

MLX_A				=	libmlx.a
MLX_A				:=	${addprefix ${MLX_DIR}/, ${MLX_A}}

######################################
#            SOURCE FILES            #
######################################
SRC					=									\
				${addprefix parsing/,					\
						get_block.c						\
						get_map.c						\
						get_textures.c					\
						open_file.c						\
						parse_utils.c					\
						parse_utils_2.c					\
						check_border.c					\
						check_border_2.c				\
						find_player.c					\
						convert_ceiling_floors_colors.c \
				}										\
				${addprefix mini_map/,					\
						draw_mini_map.c					\
						draw_line.c						\
				}										\
				${addprefix str_lst/,					\
						str_lst_add_back.c				\
						str_lst_add_front.c				\
						str_lst_clear.c					\
						str_lst_del_one.c				\
						str_lst_push_back.c				\
						str_lst_push_front.c			\
						str_new.c						\
				}										\
				${addprefix raycaster/,					\
						raycasting.c					\
						raycasting_2.c					\
						floor_casting.c					\
						floor_casting_2.c				\
						wall_casting.c					\
						wall_casting_2.c 				\
						wall_casting_3.c 				\
						free_all.c						\
						initialize_orientation.c		\
				}										\
						keys.c							\
						keys_2.c						\
						keys_3.c						\
						vectors.c						\
						get_next_line.c					\
						main.c

######################################
#            OBJECT FILES            #
######################################
OBJ					=	${SRC:.c=.o}
OBJ					:=	${addprefix ${OBJ_DIR}/, ${OBJ}}

DEP					=	${OBJ:.o=.d}

#######################################
#                FLAGS                #
#######################################
CFLAGS				=	-Wall -Wextra -Werror
CFLAGS				+=	-MMD -MP
CFLAGS				+=	-I${INC_DIR}
CFLAGS				+=	-I${FT_INC_DIR}
CFLAGS				+=	-I${MLX_INC_DIR}

LDFLAGS				=	-L${FT_DIR} -lft
LDFLAGS				+=	-L${MLX_DIR} -lmlx -lX11 -lXext
LDFLAGS				+=	-lm

ifeq (${DEBUG}, 1)
	CFLAGS	+=	-g3
	CFLAGS	+=	-DDEBUG=1
endif

#######################################
#                RULES                #
#######################################
${NAME}: ${OBJ} ${FT_A} ${MLX_A}
	${LINK} ${OBJ} ${LDFLAGS} ${OUTPUT_OPTION}

all: ${NAME}

-include ${DEP}

${OBJ_DIR}/%.o: ${SRC_DIR}/%.c
	@${MKDIR} ${@D}
	${CC} ${CFLAGS} $< ${OUTPUT_OPTION}

${FT_A}:
	${MAKE} ${@F} -C ${@D}

${MLX_A}:
	${MAKE} -C ${@D}

clean:
	${RM} ${OBJ_DIR} ${NAME} vgcore.*

fclean: clean
	${MAKE} $@ -C ${FT_DIR}
	${MAKE} clean -C ${MLX_DIR}

re: clean all

fre: fclean all

.PHONY: all clean fclean re fre

-include norm.mk
