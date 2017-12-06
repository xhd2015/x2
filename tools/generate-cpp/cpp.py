#!/usr/bin/python3
helpInfo = r'''
cpp.py 选项 模板
    选项
        -f|--gen-file  生成文件,如果没有指定生成文件，则打印到标准输出
        -k|--key        关键字，如 -k Class=v
        -h|--help       帮助
        -a|--append     是否将内容添加，如果没有此选项，就是新建文件。必须与-f一起使用
        -q|--no-std-output  不输出内容
    模板
        以.template结尾，依据前缀名生成不同的文件
    当前模板的关键字:
        h.template      -- Class
        cpp.template    -- Class HFile
            如果不提供HFile参数，默认为{Class}.h
        func.template   -- RType=void Class FuncName Args=""
'''
fnames ={
    'h':
        ['h.template',['Class'] ],
    'cpp':
        ['cpp.template',['HFile','Class']],
    'func':
        ['func.template',['RType','Class','FuncName','Args']],
}
class CppHelper:
    @staticmethod
    def fileContent(f):
        with open(f) as x:
            return x.read()
    @staticmethod
    def getRealKey(keysList,defKey,givenKey):
        x = {}
        missing = "*Missing*"
        for i in keysList:
            if i in givenKey:
                x[i] = givenKey[i]
            elif i in defKey:
                x[i] = defKey[i]
            else:
                x[i] = missing
        if "HFile" in keysList and x["HFile"]== missing:#默认HFile = Class.h
            x["HFile"] = x["Class"]+".h"
        return x
    def __init__(self,**defaultKeys):
        self.keys = defaultKeys
        if not "Args" in self.keys:
            self.keys["Args"]=""
        if not "RType" in self.keys:
            self.keys["RType"]="void"
    def make(self,fkey,**args):
        f = CppHelper.fileContent(fnames[fkey][0])
        realKey = CppHelper.getRealKey(fnames[fkey][1],self.keys,args)
        return f.format(**realKey)
    def makeH(self,**args):
        return self.make('h',**args)
    def makeCpp(self,**args):
        return self.make('cpp',**args)
    def makeFunc(self,**args):
        return self.make('func',**args)
def getDictOpts(value):
    index = value.index('=')
    return (value[:index],value[index+1:])
def getTemplateKey(templateName):
    index = templateName.index(".")
    return templateName[:index]
if __name__=='__main__':
    import sys,getopt
    args = sys.argv[1:]
    options=[
        (("--gen-file","-f"),1,"file"),#以后者作为key
        (("--help","-h"),0,"help"),
        (("--key","-k"),3,"keys"),#3 == more,dict,2 == more list
        (("--append","-a"),0,"append"),
        (("--no-std-output","-q"),0,"quiet"),
    ]
    values = {
        "keys":{},
        "file":None,
        "template":None,
        "help":None,
        "append":None,
        "quiet":None
        
    }
    short_opts='f:k:haq'
    long_opts=["gen-files=","key=","help","append","no-std-output"]
    opt,val = getopt.gnu_getopt(args,short_opts,long_opts)
    for i in opt:
        for j in options:
            if i[0] in j[0]:
                if j[1]==1:
                    values[j[2]] = i[1]
                elif j[1]==0:
                    values[j[2]] = True
                elif j[1]==2:
                    values[j[2]].append(i[1])
                elif j[1]==3:
                    k,v = getDictOpts(i[1])
                    values[j[2]][k]=v
                break
    if len(val):
        values["template"] = getTemplateKey(val[0])
    else:
        print(helpInfo)
        exit()
    
    if values["help"]:
        print(helpInfo)
    else:
        c1 = CppHelper(**values["keys"])
        x = c1.make(values["template"])
        if values["file"]:
            mode = "w+"
            if values["append"]:
                mode = "a+"
            with open(values["file"],mode) as wf:
                wf.write(x)
                wf.flush()
        if not values["quiet"]:
            print(x)