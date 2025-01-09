import re

def computeLPSArray(pat, M, lps):
    len = 0
    lps[0]
    i = 1
    while i < M:
        if pat[i] == pat[len]:
            len += 1
            lps[i] = len
            i += 1
        else:
            if len != 0:
                len = lps[len-1]
            else:
                lps[i] = 0
                i += 1

def KMPSearch(pat, text, p):

    M = len(pat)
    N = len(text)
    lps = [0]*M
    j = 0 
    computeLPSArray(pat, M, lps)
 
    i = 0 
    while i < N:
        if pat[j].lower() == text[i].lower():
            i += 1
            j += 1
 
        if j == M:
            p +=1
            j = lps[j-1]
            break

        elif i < N and pat[j].lower() != text[i].lower():
            if j != 0:
                j = lps[j-1]
            else:
                i += 1      
    return p
 


root_file=input("Enter The Name of root file ")
plagiarised_file=input("Enter The Name of plagiarised file ")
  
Text = open(root_file,"r")
text = Text.read()

pattern_file = open(plagiarised_file,"r").read()
sentences = re.split(r'[\.\?!\r\n]', pattern_file)
counter_matched = 0
counter_total = 0
p=0
for pattern in sentences:
  pattern = pattern.strip()

  if len(pattern) > 0:
    counter_total +=1
    counter_matched += KMPSearch(pattern, text,p)
          
print ("Match percentage = %s%%" % round((counter_matched*100/counter_total)))

if(counter_matched*100/counter_total) >= 70 :
  print ("The input file appears to be plagiarised. %s%% of its content matches with the file %s." % ((counter_matched*100/counter_total), root_file))