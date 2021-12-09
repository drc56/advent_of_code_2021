processFile = function(filepath) {
  con = file(filepath, "r")
  prev = NULL
  increases = 0
  while ( TRUE ) {
    line = readLines(con, n = 1)
    if ( length(line) == 0 ) {
      break
    }
    cur = strtoi(line)
    if(!is.null(prev) && cur > prev)
    {
        increases = increases + 1
    }
    prev = cur
  }
  print(increases)
  close(con)
}

processFile("input.txt")