# /bin/python3

# Input arguments are for suckers
FILE_NAME = "input.txt"

def find_increases(file_name):
    prev = None
    increases = 0
    with open(file_name) as file:
        for line in file:
            cur = int(line)
            if prev is None:
                prev = cur
            else:
                if cur > prev:
                    increases += 1
                prev = cur
            
    return increases

def main():
    print(find_increases(FILE_NAME))

if __name__ == "__main__":
    main()