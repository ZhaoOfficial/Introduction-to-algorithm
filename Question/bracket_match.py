# check if it is {[(<>)]}.
def check_hierachy(bracket):
    if bracket == '{' or bracket == '}':
        return 0
    elif bracket == '[' or bracket == ']':
        return 1
    elif bracket == '(' or bracket == ')':
        return 2
    elif bracket == '<' or bracket == '>':
        return 3

# check if it is matched
def check_match(left, right):
    if left == '{' and right == '}':
        return True
    elif left == '[' and right == ']':
        return True
    elif left == '(' and right == ')':
        return True
    elif left == '<' and right == '>':
        return True
    return False

# main
def check_bracket(brackets:str) -> bool:
    hierachy = 0
    stack = []
    for i in brackets:
        # hierachy up
        if hierachy > check_hierachy(i):
            return False
        else:
            # change hierachy
            hierachy = check_hierachy(i)
        if i == '{' or i == '[' or i == '(' or i == '<':
            stack.append(i)
        elif i == '}' or i == ']' or i == ')' or i == '>':
            bracket = stack.pop()
            # change hierarchy
            if len(stack) != 0:
                hierachy = check_hierachy(stack[-1])
            if not check_match(bracket, i):
                return False
    # if left bracket left
    if len(stack) != 0:
        return False
    return True



brackets = input()
print(check_bracket(brackets))