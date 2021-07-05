# clipboard watcher
Golang clipboard watcher for linux, using event notification of X11.

# usage
```golang
func main() {
	clipboard.Watch(func(data []byte) {
		fmt.Println(string(data))
	})
}
```

## reference
https://stackoverflow.com/questions/27378318/c-get-string-from-clipboard-on-linux/44992938#44992938
