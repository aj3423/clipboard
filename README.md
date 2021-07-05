# clipboard watcher
Golang clipboard watcher for linux, using event notification of X11.

# usage
```golang
func main() {
	// watch
	go clipboard.Watch(func(data []byte) {
		fmt.Println(string(data))
	})

	// stop watching after 15 seconds
	time.Sleep(15 * time.Second)
	clipboard.StopWatching()

	time.Sleep(time.Hour)
}
```

## reference
https://stackoverflow.com/questions/27378318/c-get-string-from-clipboard-on-linux/44992938#44992938
