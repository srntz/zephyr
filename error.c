#include "error.h"
#include <stdbool.h>

bool is_error(Error* err) {
	return err->err_code == NO_ERR ? false : true;
}