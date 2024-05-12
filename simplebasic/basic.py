import re

curr_cell_var = 99
curr_cell_comm = 0

variables = []
commands = []
start_commands = {}
queue_goto = []

basic_check_line = re.compile(r"(\d+)\s+(REM|INPUT|PRINT|LET|GOTO|IF|END)\s*(.*)")
var_check = re.compile(r"([A-Z])\s*")
num_check = re.compile(r"(-?\d+)\s*")
num_line_check = re.compile(r"(\d+)\s*")


class Variable:
    def __init__(self, title, address):
        self.title = title
        self.address = address


class CommandSA:
    def __init__(self, cell, command, operand):
        self.cell = cell
        self.command = command
        self.operand = operand


def check_presence_var(string):
    for i, variable in enumerate(variables):
        if variable.title == string:
            return i
    variables.append(Variable(string, curr_cell_var))
    return len(variables) - 1


def comm_input(operand, line):
    if not re.match(var_check, operand):
        print(f"Invalid line | Invalid variable for 'input'\n\"{line}\"")
        return -1
    operand = operand.strip()
    address_operand = check_presence_var(operand)
    commands.append(CommandSA(curr_cell_comm, "READ", variables[address_operand].address))
    return 0


def comm_print(operand, line):
    if not re.match(var_check, operand) and not re.match(num_check, operand):
        print(f"Invalid line | Invalid operand for 'print'\n\"{line}\"")
        return -1
    operand = operand.strip()
    if re.match(num_check, operand):
        temp = int(operand)
        if temp < -0x2000 or temp > 0x1FFF:
            print(f"Invalid line | The valid range for the value of the number from -0x2000 to 0x1FFF inclusive\n\"{line}\"")
            return -1
    address_operand = check_presence_var(operand)
    commands.append(CommandSA(curr_cell_comm, "WRITE", variables[address_operand].address))
    return 0


def comm_goto(operand, line):
    operand = operand.strip()
    if not re.match(num_line_check, operand):
        print(f"Invalid line | Invalid operand for 'goto'\n\"{line}\"")
        return -1

    if operand not in start_commands:
        commands.append(CommandSA(curr_cell_comm, "JUMP", int(operand)))
        queue_goto.append(len(commands) - 1)
    else:
        address_operand = start_commands[operand]
        commands.append(CommandSA(curr_cell_comm, "JUMP", address_operand))
    return 0


def comm_let(operand, line):
    let_one_param_check = re.compile(r"([A-Z])\s*=\s*([A-Z]|-?\d+)\s*")
    let_two_param_check = re.compile(r"([A-Z])\s*=\s*([A-Z]|-?\d+)\s*([\+\-\*\/])\s*([A-Z]|-?\d+)\s*")
    if not re.match(let_one_param_check, operand) and not re.match(let_two_param_check, operand):
        print(f"Invalid line | Invalid operand for 'let'\n\"{line}\"")
        return -1

    operand = operand.strip()
    if re.match(let_one_param_check, operand):  # Если один аргумент
        var, value = re.match(let_one_param_check, operand).groups()
        value = value.strip()
        if re.match(num_check, value):
            temp = int(value)
            if temp < -0x2000 or temp > 0x1FFF:
                print(f"Invalid line | The valid range for the value of the number from -0x2000 to 0x1FFF inclusive\n\"{line}\"")
                return -1
        value_address = check_presence_var(value)
        commands.append(CommandSA(curr_cell_comm, "LOAD", variables[value_address].address))
        var_address = check_presence_var(var)
        commands.append(CommandSA(curr_cell_comm, "STORE", variables[var_address].address))
    else:  # Если выражение (только простое)
        var, value1, sign, value2 = re.match(let_two_param_check, operand).groups()
        value1 = value1.strip()
        value2 = value2.strip()

        if re.match(num_check, value1):
            temp = int(value1)
            if temp < -0x2000 or temp > 0x1FFF:
                print(f"Invalid line | The valid range for the value of the number from -0x2000 to 0x1FFF inclusive\n\"{line}\"")
                return -1
        value_address1 = check_presence_var(value1)
        commands.append(CommandSA(curr_cell_comm, "LOAD", variables[value_address1].address))

        if re.match(num_check, value2):
            temp = int(value2)
            if temp < -0x2000 or temp > 0x1FFF:
                print(f"Invalid line | The valid range for the value of the number from -0x2000 to 0x1FFF inclusive\n\"{line}\"")
                return -1
        value_address2 = check_presence_var(value2)

        if sign == "+":
            commands.append(CommandSA(curr_cell_comm, "ADD", variables[value_address2].address))
        elif sign == "-":
            commands.append(CommandSA(curr_cell_comm, "SUB", variables[value_address2].address))
        elif sign == "*":
            commands.append(CommandSA(curr_cell_comm, "MUL", variables[value_address2].address))
        elif sign == "/":
            commands.append(CommandSA(curr_cell_comm, "DIVIDE", variables[value_address2].address))

        var_address = check_presence_var(var)
        commands.append(CommandSA(curr_cell_comm, "STORE", variables[var_address].address))
    return 0


def comm_end(operand, line):
    if operand.strip():
        print(f"Invalid line | There should be nothing after 'end'\n\"{line}\"")
        return -1
    commands.append(CommandSA(curr_cell_comm, "HALT", 0))
    return 0


def comm_if(operand, line):
    if_condition_check = re.compile(r"(([A-Z]|-?\d+)\s*(=|<|>)\s*([A-Z]|-?\d+)\s+(INPUT|PRINT|LET|GOTO|END)\s*(.*))")
    if not re.match(if_condition_check, operand):
        print(f"Invalid line | There should be nothing after 'if'\n\"{line}\"")
        return -1

    operand = operand.strip()
    value1, condition, value2, comm, op = re.match(if_condition_check, operand).groups()
    address_value1 = check_presence_var(value1)
    address_value2 = check_presence_var(value2)

    if condition == "=":
        commands.append(CommandSA(curr_cell_comm, "LOAD", variables[address_value1].address))
        commands.append(CommandSA(curr_cell_comm, "SUB", variables[address_value2].address))
        commands.append(CommandSA(curr_cell_comm, "JZ", curr_cell_comm + 2))
    else:
        if condition == "<":
            commands.append(CommandSA(curr_cell_comm, "LOAD", variables[address_value1].address))
            commands.append(CommandSA(curr_cell_comm, "SUB", variables[address_value2].address))
        else:
            commands.append(CommandSA(curr_cell_comm, "LOAD", variables[address_value2].address))
            commands.append(CommandSA(curr_cell_comm, "SUB", variables[address_value1].address))
        commands.append(CommandSA(curr_cell_comm, "JNEG", curr_cell_comm + 2))

    commands.append(CommandSA(curr_cell_comm, "JUMP", -1))  # пока -1
    temp = len(commands) - 1

    if comm == "INPUT":
        if comm_input(op, line):
            return -1
    elif comm == "PRINT":
        if comm_print(op, line):
            return -1
    elif comm == "LET":
        if comm_let(op, line):
            return -1
    elif comm == "GOTO":
        if comm_goto(op, line):
            return -1
    elif comm == "END":
        if comm_end(op, line):
            return -1

    commands[temp].operand = curr_cell_comm
    return 0


def main():
    import sys

    if len(sys.argv) != 3:
        print("The number of arguments does not match the condition!")
        print("The translator launch command must look like: simpleBasic file.sb file.sa, "
              "where file.sb – name of the file that contains the program in Simple Basic, "
              "file.sa - translation result")
        return -1

    if not re.match(r"\w+\.sb", sys.argv[1]):
        print(f"The extension of the first argument, \"{sys.argv[1]}\", does not match the conditions")
        print("The translator launch command must look like: simpleBasic file.sb file.sa, "
              "where file.sb – name of the file that contains the program in Simple Basic, "
              "file.sa - translation result")
        return -1

    if not re.match(r"\w+\.sa", sys.argv[2]):
        print(f"The extension of the second argument, \"{sys.argv[1]}\", does not match the conditions")
        print("The translator launch command must look like: simpleBasic file.sb file.sa, "
              "where file.sb – name of the file that contains the program in Simple Basic, "
              "file.sa - translation result")
        return -1

    try:
        with open(sys.argv[1]) as file:
            lines = file.readlines()
    except FileNotFoundError:
        print(f"Unable to open the \"{sys.argv[1]}\" file.")
        print("Check whether the file is in the directory, as well as access rights.")
        return -1

    prev_line = -1
    check_main_end = False

    for line in lines:
        match = re.match(basic_check_line, line)
        if not match:
            print(f"Invalid line\n\"{line}\"")
            return -1

        tmp = int(match.group(1))
        if prev_line >= tmp:
            print(f"Invalid line | The line number must increase and must not be repeated.\n\"{line}\"")
            return -1
        prev_line = tmp

        command = match.group(2)

        if command == "REM":
            continue
        elif command == "INPUT":
            operand = match.group(3)
            start_commands[match.group(1)] = curr_cell_comm
            if comm_input(operand, line):
                return -1
        elif command == "PRINT":
            operand = match.group(3)
            start_commands[match.group(1)] = curr_cell_comm
            if comm_print(operand, line):
                return -1
        elif command == "GOTO":
            operand = match.group(3)
            start_commands[match.group(1)] = curr_cell_comm
            if comm_goto(operand, line):
                return -1
        elif command == "LET":
            operand = match.group(3)
            start_commands[match.group(1)] = curr_cell_comm
            if comm_let(operand, line):
                return -1
        elif command == "END":
            operand = match.group(3)
            start_commands[match.group(1)] = curr_cell_comm
            if comm_end(operand, line):
                return -1
            check_main_end = True
            break
        elif command == "IF":
            operand = match.group(3)
            start_commands[match.group(1)] = curr_cell_comm
            if comm_if(operand, line):
                return -1

        if curr_cell_comm > curr_cell_var:
            print("Error! The program didn't have enough memory!")
            return -1

    if not check_main_end:
        print("Error! The main end is not found!")
        return -1

    for i in queue_goto:
        if str(commands[i].operand) not in start_commands:
            print("Invalid operand for \"goto\". | GoTo refers to a nonexistent string")
            return -1
        else:
            address_operand = start_commands[str(commands[i].operand)]
            commands[i].operand = address_operand

    try:
        with open(sys.argv[2], 'w') as file:
            for command in commands:
                file.write(f"{command.cell:02} {command.command} {command.operand:02}\n")
            for variable in reversed(variables):
                if re.match(var_check, variable.title):
                    file.write(f"{variable.address:02} = 0\n")
                else:
                    file.write(f"{variable.address:02} = {int(variable.title, 16)}\n")
    except FileNotFoundError:
        print(f"Unable to open the \"{sys.argv[2]}\" file.")
        print("Check your access rights.")
        return -1

    return 0


if __name__ == "__main__":
    main()
