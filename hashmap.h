/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 18:59:37 by pdrago            #+#    #+#             */
/*   Updated: 2024/01/26 23:18:57 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHMAP_H
# define HASHMAP_H

# include <stdlib.h>

# ifndef NONE_MALLOCED
#  define NONE_MALLOCED 0
# endif

# ifndef KEY_MALLOCED
#  define KEY_MALLOCED 1
# endif

# ifndef VALUE_MALLOCED
#  define VALUE_MALLOCED 2
# endif

# ifndef BOTH_MALLOCED
#  define BOTH_MALLOCED 3
# endif

typedef struct s_hashnode
{
	struct s_hashnode *next;
	char *key;
	int allocation_flag;
	void *value;
} t_hashnode;

typedef struct s_hashmap
{
	unsigned int max_size;
	unsigned int current_size;
	t_hashnode **array;
} t_hashmap;

void	*get(t_hashmap *hashmap, char *key);
void insert(t_hashmap *hashmap, char *key, void *value, int allocation_flag);
void insert_node(t_hashmap *hashmap, char *key, unsigned long key_index, t_hashnode *newnode);
int my_strncmp(const char *s1, const char *s2, size_t n);
size_t my_strlen(const char *s);
void *resize(t_hashmap *map);
t_hashmap *create_hashmap(unsigned int max_size);
t_hashnode *create_hashnode(char *key, void *value, int allocation_flag);
void destroy_map(t_hashmap *hashmap);
void destroy_hashnode(t_hashnode *node);
unsigned long poor_hash(char *key);

#endif
