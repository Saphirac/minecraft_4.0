# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/20 01:48:02 by mcourtoi          #+#    #+#              #
#    Updated: 2023/04/25 03:41:14 by mcourtoi         ###   ########.fr        #
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
PRV_DIR				=	private

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
SRC					=					\
				${addprefix drawing/,	\
						draw_pixel.c	\
						draw_line.c		\
						draw_mini_map.c	\
				}						\
				${addprefix parsing/,	\
						get_block.c		\
				}						\
				${addprefix raycasting/,\
						dda.c			\
				}						\
						main.c			\
						keys.c			\
						vectors.c

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

LDFLAGS				+=	-L${FT_DIR} -lft
LDFLAGS				+=	-L${MLX_DIR} -lmlx -lX11 -lXext
LDFLAGS				+=	-lm

ifeq (${DEBUG}, 1)
	CFLAGS	+=	-g
	CFLAGS	+=	-DDEBUG=1
endif

#######################################
#                RULES                #
#######################################
${NAME}: ${OBJ} ${FT_A} ${MLX_A}
	${LINK} $^ ${LDFLAGS} ${OUTPUT_OPTION}

all: ${NAME}

-include ${DEP}

${OBJ_DIR}/%.o: ${SRC_DIR}/%.c
	@${MKDIR} ${@D}
	${CC} ${CFLAGS} $< ${OUTPUT_OPTION}

${FT_A}:
	@${MAKE} ${@F} -C ${@D}

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
