#include "hashmap.h"

unsigned long poor_hash(char *key){
	if (!key) return 0;
	unsigned long hash = 0;
	int count = -1;
	while (key[++count])
		hash += key[count];
	return hash;
}

void destroy_hashnode(t_hashnode *node){
	if (node->allocation_flag == KEY_MALLOCED) free(node->key);
	else if (node->allocation_flag == VALUE_MALLOCED) free(node->value);
	else if (node->allocation_flag == BOTH_MALLOCED)
	{
		free(node->key);
		free(node->value);
	}
	free (node);
}

void destroy_map(t_hashmap *hashmap){
	t_hashnode		*current = NULL;
	t_hashnode		*next = NULL;
	unsigned int count = 0;
	while (count < hashmap->max_size)
	{
		if (hashmap->array[count] != NULL)
		{
			current = hashmap->array[count];
			while (current != NULL)
			{
				next = current->next;
				destroy_hashnode(current);
				current = next;
			}
		}
		count++;
	}
	free (hashmap->array);
	free (hashmap);
}
t_hashnode *create_hashnode(char *key, void *value, int allocation_flag){
	if (!value || !key) return NULL;
	t_hashnode *n = (t_hashnode *) malloc (sizeof(t_hashnode));
	if (!n) return NULL;
	n->key = key;
	n->value = value;
	n->next = NULL;
	n->allocation_flag = allocation_flag;
	return n;
}

t_hashmap *create_hashmap(unsigned int max_size){
	if (max_size < 1) return NULL;
	t_hashmap *map = (t_hashmap *) malloc (sizeof(t_hashmap));
	if (!map) return NULL;
	map->array = (t_hashnode **) malloc (sizeof(t_hashnode *) * max_size);
	if (!map->array) return NULL;
	map->max_size = max_size;
	map->current_size = 0;
	unsigned int count = 0;
	while (count < max_size)
		map->array[count++] = NULL;
	return map;
}

void *resize(t_hashmap *map){
	t_hashmap *newmap = create_hashmap(map->current_size + 20);
	if (!newmap) return NULL;
	unsigned int count = 0;
	while (count < map->current_size)
	{
		if (map->array[count] != NULL)
		{
			newmap->array[poor_hash(map->array[count]->key) % newmap->max_size] = map->array[count];
			newmap->current_size++;
		}
		count++;
	}
	destroy_map(map);
	map = newmap;
	return map;
}

size_t my_strlen(const char *s){
	size_t len = 0;
	while (s && s[len])
		len++;
	return len;
}

int my_strncmp(const char *s1, const char *s2, size_t n){
	unsigned int count = 0;
	if (n == 0) return 0;
	while ((((unsigned char) s1[count]) == ((unsigned char) s2[count]))
		&& (s1[count]) && (s2[count]) && (--n))
		count++;
	return ((unsigned char) s1[count] - (unsigned char) s2[count]);
}

void insert_node(t_hashmap *hashmap, char *key, unsigned long key_index, t_hashnode *newnode){
	if (hashmap->array[key_index] == NULL)
	{
		hashmap->array[key_index] = newnode;
		return ;
	}
	if (!my_strncmp((const char *) hashmap->array[key_index]->key
			, (const char *)key, my_strlen((const char *) key)))
	{
		destroy_hashnode(hashmap->array[key_index]);
		hashmap->array[key_index] = newnode;
		return ;
	}
	t_hashnode *current = hashmap->array[key_index];
	while (current->next != NULL)
		current = current->next;
	current->next = newnode;
}

void insert(t_hashmap *hashmap, char *key, void *value, int allocation_flag){
	if (!hashmap || !key || !value) return ;
	hashmap->current_size++;
	if (hashmap->current_size > hashmap->max_size)
		if (!resize(hashmap)) return ;
	unsigned long key_index = poor_hash(key) % hashmap->max_size;
	t_hashnode *newnode = create_hashnode(key, value, allocation_flag);
	if (!newnode) return ;
	insert_node(hashmap, key, key_index, newnode);
}

void *get(t_hashmap *hashmap, char *key){
	if (!hashmap || !key) return NULL;
	unsigned long key_index = poor_hash(key) % hashmap->max_size;
	if (hashmap->array[key_index] == NULL) return NULL;
	if (hashmap->array[key_index]->next == NULL) return hashmap->array[key_index]->value;
	t_hashnode *current = hashmap->array[key_index];
	while (current != NULL && my_strncmp((const char *) current->key, (const char *) key, my_strlen((const char *) key)))
		current = current->next;
	return current->value;
}
/*
#include <stdio.h>
typedef struct teste
{
	int numero;
	char *string;
	struct teste *structs;
}teste;
int main(void)
{
	teste a;
	teste b;

	a.numero = 25;
	a.string = "it works";
	a.structs = &b;
	b.string = "it really works";

	t_hashmap *pessoa = create_hashmap(50);
	insert(pessoa, "teste", &a, NONE_MALLOCED);
	printf("%i\n", ((teste *) get(pessoa, "teste"))->numero);
	printf("%s\n", ((teste *) get(pessoa, "teste"))->string);
	printf("%s\n", ((teste *) get(pessoa, "teste"))->structs->string);
	destroy_map(pessoa);
	t_hashmap *pessoa_collision = create_hashmap(10);
	printf("This collision example happens with a 10 size array and these 2 strings: \"CPF\" have hash index: %lu | \"Drago\" have hash index: %lu\n", poor_hash("cpf") % pessoa_collision->max_size, poor_hash("Drago") % pessoa_collision->max_size);
	insert(pessoa_collision, "cpf", "123.123.123-12", NONE_MALLOCED);
	insert(pessoa_collision, "Drago", "It deals with collision!", NONE_MALLOCED);
	printf("%s\n", (char *) get(pessoa_collision, "cpf"));
	printf("%s\n", (char *) get(pessoa_collision, "Drago"));
	printf("%s\n", (char *) get(pessoa_collision, "cpf"));
	printf("%s\n", (char *) get(pessoa_collision, "Drago"));
	destroy_map(pessoa_collision);
}
*/
