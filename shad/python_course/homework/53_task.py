import sys, traceback

def run_user_code():
    with open("broken_module.py",'rb') as f:
        command = ""
        command2 = []
        while True:
            line=f.readline()
            if not line: break
            command += (line + '\n')
            command2.append(line + '\n')
    
    flag = False
    #while (!flag)
    try:
        flag = True
        exec ''.join(command2)
    except:
        exc_traceback = sys.exc_info()
        print "Exception in user code:"
        print '-'*60
        #traceback.print_exc(file=sys.stdout)
        traceback.format_tb(exc_traceback)
        print exc_traceback.tb_lineno
        print '-'*60
        flag = False

run_user_code()
