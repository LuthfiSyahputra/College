

debugPrint = bool(False)
class Debug:
    errCode = [
        "errcode[0] {Buffer Overflow}",
        "errcode[1] {undefined Parameters}",
        "errcode[2] {Unexpected Value}"
    ]


    def __init__(self) -> None:
        self.errFreq = [0 for i in range(0, len(self.errCode))]
        self.ierrFreq = [0 for i in range(0, len(self.errCode))]
        pass

    def error(self, errcode, isprinted:bool = True, note: str = "debug"):

        if(errcode >= 10):
            errcode -= 10
            self.ierrFreq[errcode] += 1

        self.errFreq[errcode] += 1

        isprinted = debugPrint
        if(isprinted == True): print(self.errCode[errcode] + " : " + note)
        return self.errCode[errcode]
    
    def iserror(self, retval, _errcode: int = None):
        if(_errcode != None): return (self.errCode[_errcode] == retval)

        for i in range(0, len(self.errCode)):
            if (self.errCode[i] == retval): return True
        return False

_globalDebug = Debug()

class token:
    _buf = str("")

    delimiter = str("")
    tokenptr = int(0)
    ntoken = int(0)
    _lastchar = str()
    
    def gettoken(self, buf, fptr, delimiter):
        self._buf = buf
        self.delimiter = delimiter

        ptr = fptr
        fchar = int(-1) # First Character
        lchar = int(0)  # Last Character


        if(ptr >= len(buf)):
            return _globalDebug.error(1, True,"token.gettoken() - fptr out of bounds: " + str(ptr))
        elif(ptr < 0):
            return _globalDebug.error(1, True, "token.gettoken() - string pointer cannot be negative(-), fptr: " + str(fptr))
        

        while ((ptr < len(buf)) and (_chseek(buf[ptr], delimiter) == False)):

            # character ptr
            if(_isblank(buf[ptr]) == False):
                if(fchar == -1): fchar = ptr
                lchar = ptr

            ptr += 1

        self.tokenptr = ptr + 1 # points to the next character after delimiter
        return buf[fchar : lchar + 1]
    
    def nexttoken(self, delimiter: str = "", buf:str = None):
        if(delimiter != ""): 
            self.delimiter = delimiter

        if(buf == None):
            if(self._buf == ""): return ""

        elif(self._buf != buf): 
            self._buf = buf
            self.tokenptr = 0
            self.ntoken = 0

        self.ntoken += 1
        return self.gettoken(self._buf, self.tokenptr, self.delimiter)

class strline:
    __linetoken = token()
    nline = int(0)

    def getline(self, buf: str, initPtr: int) -> str:
        return self.__linetoken.gettoken(buf, initPtr, '\n')
    
    def nextline(self, buf:str = None) -> str:
        retstr = self.__linetoken.nexttoken('\n', buf)
        self.nline = self.__linetoken.ntoken
        return retstr

    def getTotalLine(self, buf: str):
        nline = int(0)
        for i in range(0, len(buf)):
            if(buf[i] == '\n'):
                nline += 1
        return nline + 1
    
    def getnline(self, buf, nline):
        if (nline <= 0):
            return _globalDebug.error(1, True, "strline.getnline() - nline cannot below 1, nline: " + str(nline))
        
        tempnline = 1
        ptr = 0

        while(tempnline != nline):
            if (ptr >= len(buf)) : return _globalDebug.error(0, True, "strline.getnline() failure - possibly out of bound line, last_line: " + str(tempnline) + " req. nline (parameter): " + str(nline))
            if (buf[ptr] == '\n'): tempnline += 1
            ptr += 1

        return self.getline(buf, ptr)



class csv:
    buf = str()
    _fptr = int()

    row = int()
    size = int()
    _nline = int()

    ndata = int(0)
    nrow = int(0)
    data = str()

    cur_row = int(0)

    _token = token()
    _line = strline()


    nattribute = int(0)
    delimiter = ""

    attributes = str()

    datatype = str()
    dataname = str()


    valid_datatype= [
        "str",
        "int",
        "float",
        "category",
        "%"
    ]


    def __init__(self, filename, delimiter) -> None:
        self.file = open(filename, "r+")
        self.buf = self.file.read()
        self.size = self.file.tell()
        self._nline = self._line.getTotalLine(self.buf)
        self.delimiter = delimiter

        self.maindata = self.getnrow()
        
        self.file.seek(0)
        pass

    
    def _getrow(self, n):
        tempstr = self._line.getnline(self.buf, n)
        if (_globalDebug.iserror(tempstr)): return tempstr

        self.cur_row = n
        retval = []
        
        while(True):
            tempval = self._token.nexttoken(self.delimiter + '\n', tempstr)
            if(tempval == _globalDebug.error(11, True, "intended for csv._getrow()")): break
            retval.append(tempval)

        return retval
    
    def nextrow(self, n:int = None):
        if(n != None): pass

        self.cur_row += 1
        return self._getrow(self.cur_row)
    
    def getnrow(self, n:int = None):
        if (self.nattribute == 0):
            _globalDebug.error(1, True, "csv.getnrow - attribute not defined - calling csv.getDataAttribute()")
            self.getDataAttribute()

        self.nrow = 0
        self.data = []
        temprow = ""

        # get row
        while(True):
            if((n != None) and (self.nrow >= n)): break
            
            temprow = self.nextrow()

            # iterate to the end of file
            if(_globalDebug.iserror(temprow) == True): break


            if(len(temprow) > 0):
                self.data.append(
                    _arrnewcpy(temprow,
                    len(temprow) if (len(temprow) <= self.nattribute) else self.nattribute,
                    self.nattribute, ""
                    ))
                self.nrow += 1

        return self.data
    

    def getDataAttribute(self):
        if(self.delimiter == ""):
            _globalDebug.error(1, True, "csv.getDataAttribute() - csv.delimiter not set \"\"")

        line = 1
        # get raw data
        while(self.nattribute == 0): 
            if(line > self._nline): 
                return _globalDebug.error(2, True, "csv.getDataAttribute() No data in the file, nline: " + str(self._nline) + "  size: " + str(self.size))
            
            tempstr = self._getrow(line)
            self.nattribute = len(tempstr)
            line += 1

        # default for datatype (if not specified)
        self.datatype = ["str" for i in range(0, self.nattribute)]
        self.dataname = [("data " + str(i)) for i in range(0, self.nattribute)]

        # datatype separation from raw data
        for n in range(0, self.nattribute):
            tempdataname = self._token.gettoken(tempstr[n], 0, "([{")
            tempdatatype = str("")

            # check the possible candidate (with string overflow safety)
            if(len(tempdataname) < len(tempstr[n])):
                tempdatatype = self._token.nexttoken(")]}")

                # check the validity from dataabase
                if (_strseek(self.valid_datatype, tempdatatype) == -1):
                    return _globalDebug.error(2, True, "csv.getDataAttribute() invalid datatype, datatype: " + tempdatatype + "  col: " + str(n+1))

                elif (len(tempdatatype) != 0): self.datatype[n] = tempdatatype

            if(len(tempdataname) != 0): self.dataname[n] = tempdataname

        
        return (self.dataname, self.datatype)
            

def _arrnewcpy(arr_template, sizeof_template, nlen, init_val):
    newarr = [init_val for i in range(0, nlen)]
    _arrcpy(arr_template, newarr, sizeof_template)
    return newarr

def _arrcpy(_from, _to, n):
    for i in range(0, n):
        _to[i] = _from[i]

def _chseek(c, delimiter):
    for i in range(0, len(delimiter)):
        if (c == delimiter[i]): return True
    return False

def _strseek(collection, str):
    if(len(str) == 0): return -2
    for i in range(0, len(collection)):
        if(collection[i] == str): return i
    return -1

def _isblank(c):
    return ((c == ' ') or (c == '\t') or (c == '\n'))



a = csv("data", ";")

for i in range(0, len(a.maindata)):
    print(a.maindata[i])