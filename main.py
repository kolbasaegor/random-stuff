error0 = 'E0: Input file is malformed'
error1 = "E1: A state 's' is not in the set of states"
error2 = 'E2: Some states are disjoint'
error3 = "E3: A transition 'a' is not represented in the alphabet"
error4 = 'E4: Initial state is not defined'
error5 = 'E5: FSA is nondeterministic'

non_deterministic = False
visited = []


def parse_input(s):
    if (s.find("states=[") != -1 or s.find("alpha=[") != -1 or s.find("initial=[") != -1 or s.find("accepting=[") != -1)\
            and s.rfind("]") != -1:
        s_ = s[s.find('[') + 1:s.rfind(']')]
        if len(s_) == 0:
            return []
        else:
            return s_.split(',')

    elif s.find("trans=[") != -1 and s.rfind("]") != -1:
        global non_deterministic
        transition_ = {}
        list_of_transitions = s[s.find('[') + 1:s.rfind(']')].split(',')
        if len(list_of_transitions[0]) == 0:
            return transition_
        else:
            for i in range(len(list_of_transitions)):
                sub_list = list_of_transitions[i].split('>')
                if not non_deterministic:
                    if (sub_list[0], sub_list[1]) in transition_.keys():
                        non_deterministic = True

                transition_[sub_list[0], sub_list[1]] = sub_list[2]
            return transition_
    else:
        return error0


def check_e1(lst, states_):
    if isinstance(lst, list):
        for item in lst:
            if item not in states_:
                return item
    elif isinstance(lst, dict):
        for item in lst.keys():
            if item[0] not in states_:
                return item[0]
            elif lst[item] not in states_:
                return lst[item]
    return 0


def check_e2(tr_, st_):
    if len(st_) > 1:
        for state in st_:
            flag = False
            for keys in tr_.keys():
                if keys[0] == state:
                    if tr_[keys] != state:
                        flag = True
                        break
                elif tr_[keys] == state:
                    if keys[0] != state:
                        flag = True
                        break
            if not flag:
                return 1
    return 0


def check_e3(lst, alpha_):
    for item in lst.keys():
        if item[1] not in alpha_:
            return item[1]
    return 0


def check_e4(lst):
    if len(lst) == 0:
        return error4
    else:
        return 0


def check_e5():
    if non_deterministic:
        return error5
    else:
        return 0


def path42(state1, state2, trans):
    s = ''
    for keys in trans.keys():
        if state1 == keys[0] and state2 == trans[keys]:
            s += keys[1]+'|'
    if state1 == state2:
        s += 'eps|'
    if s == '':
        s += '{}'
    else:
        s = s[:-1]+''
    return s


def simba(R, n, m):
    pimpa = [[''] * m for i in range(n)]
    for i in range(n):
        for j in range(m):
            pimpa[i][j] = R[i][j]
    return pimpa


def fsa_to_reg(states, initial, accepting, trans):
    n = len(states)
    for i in range(n):
        if states[i] == initial[0]:
            temp = states[0]
            states[0] = states[i]
            states[i] = temp
    R = [[''] * n for i in range(n)]

    for i in range(n):
        for j in range(n):
            R[i][j] = path42(states[i], states[j], trans)

    copy = simba(R, n, n)
    for k in range(n):
        for i in range(n):
            for j in range(n):
                R[i][j] = '('+copy[i][k]+')(' + copy[k][k] + ')*('+copy[k][j]+')|('+copy[i][j]+')'
        copy = simba(R, n, n)

    ans = ''
    for i in accepting:
        for j in range(n):
            if states[j] == i:
                index = j
        ans += R[0][index] + '|'
    if ans == '':
        ans = '{}'
    else:
        ans = ans[:-1]

    return ans


def main():
    f = open('input.txt')
    inpt = []
    for line in f:
        inpt.append(line)
    f.close()
    states = parse_input(inpt[0])
    alpha = parse_input(inpt[1])
    initial = parse_input(inpt[2])
    accepting = parse_input(inpt[3])
    trans = parse_input(inpt[4])

    f = open('output.txt', 'w')

    if states == error0 or alpha == error0 or initial == error0 or accepting == error0 or trans == error0:
        f.write('Error:'+'\n')
        f.write(error0+'\n')
    else:
        current_test = check_e1(initial, states)
        if current_test == 0:
            current_test = check_e1(accepting, states)
            if current_test == 0:
                current_test = check_e1(trans, states)
                if current_test != 0:
                    f.write('Error:'+'\n')
                    f.write('E1: A state ' + current_test + ' is not in the set of states')
            else:
                f.write('Error:'+'\n')
                f.write('E1: A state ' + current_test + ' is not in the set of states')
        else:
            f.write('Error:'+'\n')
            f.write('E1: A state '+current_test+' is not in the set of states')

        if current_test == 0:
            current_test = check_e2(trans, states)
            if current_test != 0:
                f.write('Error:'+'\n')
                f.write(error2+'\n')
            else:
                current_test = check_e3(trans, alpha)
                if current_test != 0:
                    f.write('Error:'+'\n')
                    f.write('E3: A transition '+current_test+' is not represented in the alphabet'+'\n')
                else:
                    current_test = check_e4(initial)
                    if current_test != 0:
                        f.write('Error:'+'\n')
                        f.write(error4+'\n')
                    else:
                        current_test = check_e5()
                        if current_test != 0:
                            f.write('Error:'+'\n')
                            f.write(error5+'\n')

    if current_test == 0:
        f.write(fsa_to_reg(states, initial, accepting, trans))

    f.close()


main()




