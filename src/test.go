package main
type float float32
import "fmt"

func main() {
   var numbers =[9]int{}
   for num:=9;num>0;num--{
      numbers[9-num]=num
   }
   
   println(numbers)

   }
   
}
