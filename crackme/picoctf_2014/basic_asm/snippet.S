## This file is in AT&T syntax - see http: www.imada.sdu.dk/Courses/DM18/Litteratur/IntelnATT.htm 
## and http://en.wikipedia.org/wiki/X86_assembly_language#Syntax. Both gdb and objdump produce
## AT&T syntax by default.
.text
.globl main

main:
    MOV $22075,%ebx                 # ebx = 22075
    MOV $17136,%eax                 # eax = 17136
    MOV $2087,%ecx                  # ecx = 2087
    CMP %eax,%ebx                   # compare $ebx to $eax (22075 to 17136)
                                    # CMP -> This compare dest to src
    JL L1                           # if (dest < src) { goto L1 } = if (22075 < 17136) { goto L1 }
    JMP L2                          # else { goto L2 }
    
    ## Label 1 (dead code)
    L1:
    IMUL %eax,%ebx
    ADD %eax,%ebx
    MOV %ebx,%eax
    SUB %ecx,%eax
    JMP L3

    ## Label 2
    L2:
    IMUL %eax,%ebx                  # ebx = eax * ebx = 17136 x 22075 = 378277200
                                    # IMUL -> This multiplies src by dest and stores the result in dest
    SUB %eax,%ebx                   # ebx = ebx - eax = 378277200 - 17136 = 378260064
                                    # SUB -> This substract src from dest and stores the result in dest
    MOV %ebx,%eax                   # eax = ebx = 378260064
    ADD %ecx,%eax                   # eax = eax + ecx = 378260064 + 2087 = 378262151
                                    # ADD -> This add src and dest and stores the result in dest 
            
    ## Label 3 (does nothing)
    L3:
    NOP                             # eax = 378262151
