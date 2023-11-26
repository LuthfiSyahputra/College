
class token:
    _buf = str()

    delimiter = str(0)
    tokenptr = int(0)
    ntoken = int(0)
    
    def gettoken(self, buf, fptr, delimiter):
        self._buf = buf
        self.delimiter = delimiter

        ptr = fptr
        fchar = int(-1) # First Character
        lchar = int(0)  # Last Character

        if(ptr >= len(buf)):
            print("buf_ptr out of bounds: ", ptr)
            return ""

        while ((ptr < len(buf)) and (_chseek(buf[ptr], delimiter) == False)):
            # character ptr
            if(_isblank(buf[ptr]) == False):
                if(fchar == -1): fchar = ptr
                lchar = ptr

            ptr += 1

        self.tokenptr = ptr
        return buf[fchar : lchar + 1]
    
    def nexttoken(self, delimiter: None, buf: None):
        if(delimiter != None): 
            self.delimiter = delimiter

        if(buf == None):
            if(self._buf == ""): return ""

        elif(self._buf != buf): 
            self._buf = buf
            self.tokenptr = 0
            self.ntoken = 0

        self.ntoken += 1
        if(self.ntoken > 1): self.tokenptr += 1
        return self.gettoken(self._buf, self.tokenptr, self.delimiter)

class strline:
    __linetoken = token()
    nline = int(0)

    def getline(self, buf: str, initPtr: int) -> str:
        return self.__linetoken.gettoken(buf, initPtr, '\n')
    
    def nextline(self, buf: None) -> str:
        retstr = self.__linetoken.nexttoken('\n', buf)
        nline = self.__linetoken.ntoken
        return retstr
    
    def getnline(buf):
        nline = int(0)
        for i in range(0, len(buf)):
            if(buf[i] == '\n'):
                nline += 1
        return nline + 1

class csv:
    fptr = int()
    row = int()
    size = int()
    bufptr = int(0)
    ndata = int(0)
    lineptr = []

    _token = token()
    _line = strline()

    nattribute = int(0)
    delimiter = ""


    def __init__(self, filename) -> None:
        self.file = open(filename, "r+")
        self.buf = self.file.read()
        self.size = self.file.tell()
        self._nline = self._line.getnline(self.buf)
        
        pass

    
    def getrow(self):
        pass
    
    def getDataAttribute(self):
        if(self.delimiter == ""):
            print("Error: Delimiter not set")
            return 0
        
        
def getToken(buf, bufptr, delimiter) -> str:
    return 0


def _isblank(c):
    return ((c == ' ') or (c == '\t') or (c == '\n'))

def _chseek(c, delimiter):
    for i in range(0, len(delimiter)):
        if (c == delimiter[i]): return True
    return False


def dataAttribute():
    return 3
    
a = csv("data")

# print(a.buf)
# print(a._token.nexttoken(";\n", a.buf))

for i in range (0, 7):
    # print(str(i) + "  - " + str(a._token.nexttoken(";\n", a.buf)))
    print(a._line.nextline(a.buf))

strr = "ewew"

print(len(a.buf))