package clipboard

/*
#cgo LDFLAGS: -lX11 -lXext -lXfixes
#include "c.h"
*/
import "C"

var user_callback func([]byte)

func Watch(cb func(data []byte)) {
	user_callback = cb

	C.WatchClipboard()
}

func StopWatching() {
	C.StopWatchingClipboard()
}
