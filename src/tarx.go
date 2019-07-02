package main

import (
	. "fmt"
	"log"
	"os"
	"os/exec"
	"os/user"
)

const TARGZ = 1
const BZ2 = 2

func Use(vals ...interface{}) {
	for _, val := range vals {
		_ = val
	}
}
func ErrorCheck(err error) {
	if err != nil {
		panic(err)
	}
}

// 封装f：为传入的函数增加defer
// func ErrorHandler() {
// 	return func() {
// 		defer func() {
// 			if r := recover(); r != nil {
// 				log.Println("GOT ERROR: ", r)
// 			}
// 		}()

// 	}
// }
func showUsage() {
	println("Usage for tarx :")
	println("     tarx <file_addr>")
	println("   tarx wil decompress the file in current dictionary")
	return 
}
func argvCheck() (int, string) {
	argv := os.Args
	if len(argv) != 2 {
		showUsage()
	}
	file, err := os.Open(argv[1])
	if nil != err || os.IsExist(err) {
		log.Fatalln(argv[1] + " is invalid or file doesn't exist !!!")
	}
	defer file.Close()
	str := argv[1]
	if str[len(str)-7:] == ".tar.gz" {
		return TARGZ, str
	} else if str[len(str)-8:] == ".tar.bz2" {
		return BZ2, str
	} else {
		log.Fatalln("unsupported file type !!!")
		return 0,str
	}
}
func CreateLog(out []byte) {
	user, _ := user.Current()
	// prefix:="("+user.Username+":"+user

	tarx_log, err := os.Create("./tarx.log")
	defer tarx_log.Close()
	if nil != err {
		log.Fatalln("open file failed !!!")
	}

	logfile := log.New(tarx_log, "[ "+user.Username+" ] ", log.LstdFlags)
	logfile.Println(out)

}
func main() {

	file_type, file_addr := argvCheck()
	var cmd *exec.Cmd
	if file_type == TARGZ {
		cmd = exec.Command("tar", "-zxvf", file_addr)
	} else if file_type == BZ2 {
		cmd = exec.Command("tar", "-jxvf", file_addr)
	}

	out, err := cmd.CombinedOutput() //标准输出 标准错误 组合
	//out, err := cmd.Output()
	//Output()和CombinedOutput()不能够同时使用，
	// 因为command的标准输出只能有一个，同时使用的话便会定义了两个，便会报错
	if err != nil {
		log.Fatalln(err)
	}
	CreateLog(out)
	Println(string(out))
	return
}
