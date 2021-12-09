package main

import (
	"fmt" 
	"os"
	"log"
	"bufio"
	"strconv"
)

func main() {
	// declare and initialize in one line without declaring type 
	// woohoo go sacrifice readability but #memory
	file, err := os.Open("input.txt")

	if err != nil{ // really fucking nil, fuck you go
		log.Fatal(err)
	}

	// not sure why I need this
	defer file.Close()

	scanner := bufio.NewScanner(file)

	increases := 0
	prev := 0
	have_prev := 0

	for scanner.Scan(){
		cur, err  := strconv.Atoi(scanner.Text())
		if err != nil{
			log.Fatal(err)
		}
		// Woohoo bad code but it works so not fixing it
		if(have_prev != 0 && cur > prev){
			increases++
			prev = cur
		} else{
			have_prev = 1
			prev = cur
		}
		prev = cur
	}
	fmt.Println(increases)

}