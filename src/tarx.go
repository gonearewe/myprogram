package main

import (
   //"os/exec"
   "os"
   "log"
   //. "fmt"
   "os/user"
)
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
func ErrorHandler()  {
	return func() {
		defer func() {
			if r := recover(); r != nil {
				log.Println("GOT ERROR: ", r)
			}
		}()

		
	}
}

func main() {
    
    user,_:=user.Current()
   // prefix:="("+user.Username+":"+user

    tarx_log,err:=os.Create("./tarx.log")
    defer tarx_log.Close()
    if nil!=err{
        log.Fatalln("open file failed !!!")
    }
    
    logfile:=log.New(tarx_log,"[ "+user.Username+" ] ",log.LstdFlags)
    logfile.Println("dddddd")
    logfile.Println("dddddd")
    logfile.Println("d6666d")
    logfile.Println("ddfffddd")
    logfile.Println("dddddd")

//    cmd := exec.Command("ls","-l")
//    out,err := cmd.CombinedOutput()//标准输出 标准错误 组合
//    //out, err := cmd.Output()
//    //Output()和CombinedOutput()不能够同时使用，
//    // 因为command的标准输出只能有一个，同时使用的话便会定义了两个，便会报错
//    if err != nil {
//       log.Fatal(err)
//    }
//    Println(string(out))
   
}