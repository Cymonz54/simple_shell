#include "shell.h"

/**
 * add_node - Adds a new node to the beginning of the list
 * @head: Address of the pointer to the head node
 * @str: String field of the new node
 * @num: Node index used by history
 *
 * Return: Size of the list
 */

list_t *add_node(list_t **head, const char *str, int num)

{
	list_t *new_node;

	if (!head)
		return (NULL);

	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);

	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;

	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	new_node->next = *head;
	*head = new_node;

	return (new_node);
}

/**
 * add_node_end - Adds a node to the end of the linked list
 * @head: Address of a pointer to the head node
 * @str: String field of the node
 * @num: Node index used by history
 *
 * Return: Size of the linked list
 */

list_t *add_node_end(list_t **head, const char *str, int num)

{
	list_t *new_node, *node;

	if (!head)
		return (NULL);
	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	memset(new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_list_str - Prints only the "str" element of a list_t linked list
 * @h: Pointer to the first node
 *
 * Return: Number of nodes in the list
 */

size_t print_list_str(const list_t *h)
{
	size_t count = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		count++;
	}
	return (count);
}

/**
 * delete_node_at_index - Deletes the node at the given index
 * @head: Address of pointer to the first node
 * @index: Index of the node to delete
 *
 * Return: 1 on success, 0 on failure
 */

int delete_node_at_index(list_t **head, unsigned int index)

{
	list_t *prev, *current;
	unsigned int i;

	if (!head || !(*head))
		return (0);
	current = *head;
	if (index == 0)
	{
		*head = current->next;
		free(current->str);
		free(current);
		return (1);
	}
	for (i = 0; current && i < index; i++)
	{
		prev = current;
		current = current->next;
	}
	if (!current)
		return (0);
	prev->next = current->next;
	free(current->str);
	free(current);

	return (1);
}

/**
 * free_list - Frees all the nodes of the list
 * @head_ptr: Address of thepointer to the head node
 *
 * Return: void
 */

void free_list(list_t **head_ptr)

{
	list_t *current, *next;

	if (head_ptr == NULL || *head_ptr == NULL)
		return;
	current = *head_ptr;

	while (current != NULL)
	{
		next = current->next;
		free(current->str);
		free(current);
		current = next;
	}

	*head_ptr = NULL;
}
