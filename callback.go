package clipboard

import "C"
import (
	"unsafe"
)

//export GoCallback
func GoCallback(out *C.char, out_len C.int) {
	slice := C.GoBytes(unsafe.Pointer(out), out_len)

	if user_callback != nil {
		user_callback(slice)
	}
}
