package main

import (
	"io/ioutil"
	"flag"
	"fmt"
	"log"
	"os"
	"os/exec"
)
var ERR_FILE
func ErrorCheckFatal(err error) {
	if nil != err {
		log.Fatal(err)
	}
}

func AddrExists(path string) (bool) {
	_, err := os.Stat(path)
	if err == nil {
		return true
	}else {
		return false
	}	
}

var (
	flag_list, flag_help, flag_config bool
	trash_name                        string
)

func init() {
	  flag.BoolVar(&flag_list,"l", false, "list stuff in the trash bin")
	  flag.BoolVar(&flag_help,"h", false, "show usage")
	  flag.BoolVar(&flag_config,"c", false, "configure the config file")

	  flag.StringVar(&trash_name,"d", "", "specify the trash (file or dictionary) name")

	// 改变默认的 Usage

	flag.Usage = usage

}
func main() {

	flag.Parse()
	if flag_help==true{
		usage()
	}else if flag_config == true {
		cmd := exec.Command("code", "-r","/opt/myprogram/etc/del_config.json")
		_, err := cmd.CombinedOutput()
		ErrorCheckFatal(err)
		
	}else if trash_name!=""{
		if AddrExists(trash_name){
			conf:=readConfigFile()
			cmd := exec.Command("mv",trash_name,trash_bin_addr)
		_, err := cmd.CombinedOutput()
		}else{
			fmt.Println("Trash Doesn't Exist or Inaccess !!!")
			fmt.Println("Please Check : "+trash_name)
			return
		}
	}
		
	
	

}
func usage() {
	fmt.Fprintf(os.Stderr, `del version: 1.0
Usage: del [-hlc] [-d trash name] [-c ]

Options:
`)
	flag.PrintDefaults()
}
type config struct{
	trash_bin_path string
}
func readConfigFile() conf config{
	if contents,err:=ioutil.ReadFile("/opt/myprogram/etc/del_config.json");err!=nil{
		fmt.Println("Un able to")
	}
}