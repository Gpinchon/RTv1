#include "mlx_framework.h"
#include "internal_framework.h"

void	destroy_objects(t_generic *from_object)
{
	t_generic	*obj[2];

	obj[0] = from_object;
	while (obj[0])
	{
		obj[1] = obj[0]->next;
		free(obj[0]);
		obj[0] = obj[1];
	}
}

void	*append_object(t_generic *new_object, t_generic *from_object)
{
	while (from_object->next)
		from_object = from_object->next;
	new_object = (t_generic *)new_object;
	new_object->prev = from_object;
	return (from_object->next = new_object);
}