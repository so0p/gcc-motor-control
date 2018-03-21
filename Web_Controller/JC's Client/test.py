@app.route('/')
@app.route('/wilbur', methods=['GET', 'POST'])
def index():
    if request.method == "GET":
        return render_template("wilbur.html")

# essentially returning true or false then whichever one returns true 
# set that value and package it and downstream it to the rover
# extra print statements are for debugging purposes and will be removed
# after debugging is complete

    if request.form["submit"] == "Forward":
        direction = 1
        success = process("Moving Forward")
        return render_template("wilbur.html", roverDirection="Successful 1" if success else "Failed 1")

    elif request.form["submit"] == "Backward":
        direction = 2
        success = process("Moving Backward")
        return render_template("wilbur.html", roverDirection="Successful 2" if success else "Failed 2")

    elif request.form["submit"] == "Left":
        direction = 3
        success = process("Moving Left")
        return render_template("wilbur.html", roverDirection="Successful 3" if success else "Failed 3")

    elif request.form["submit"] == "Right":
        direciton = 4
        success = process("Moving Right")
        return render_template("wilbur.html", roverDirection="Successful 4" if success else "Failed 4")

# pack and send here

p_direction = chr(direction)
values = (chr(183), p_direction, chr(0), chr(0), chr(237))
s = struct.Struct('c c c c c')
data = s.pack(*values)

TCP_IP='10.22.0.11'
TCP_PORT = 23
BUFFER_SIZE = 1024

s=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((TCP_IP,TCP_PORT))
s.send(mybytes)

s.close()


