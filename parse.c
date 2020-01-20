#include "scop.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int check_error_obj(t_obj *obj)
{
	if (obj->v.size == -1 || obj->vp.size == -1 
		|| obj->vn.size == -1 || obj->vt.size == -1 
		|| obj->p_size == -1 || obj->l_size == -1 
		|| obj->f_size == -1)
		return (obj->error = 1);
	return(0);
}

t_obj parse(char *filename)
{
	int		fd;
	char	*buffer;
	t_obj	obj;
	int j;

	obj = init_obj();
	if (obj.error || (fd = open(filename, O_RDONLY)) < 0)
		return (obj);
	j = 1;
	while (get_next_line(fd, &buffer) == 1)
	{
		parse_all_vert(buffer, &obj);
		if (check_error_obj(&obj))
		{
			printf("###### parse error line : %d ######\n", j);
			return (obj);
		}
		ft_memdel((void**)&buffer);
		j++;
	}
	ft_memdel((void**)&buffer);
	if (DEBUG)
		print_obj(obj);
	return (obj);
}