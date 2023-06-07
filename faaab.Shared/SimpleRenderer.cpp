//
// This file is used by the template to render a basic scene using GL.
//
#include "pch.h"

#include "SimpleRenderer.h"
#include "MathHelper.h"

// These are used by the shader compilation methods.
#include <vector>
#include <iostream>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>
#include <thread>
#include <assert.h>
#include <chrono>
#include <future>
#include <stdexcept>
using namespace std;

bool yyn = false;
bool yon = false;
int udpSd;
int tcpSd;
int clientSd;
int tcptd[200];
string dt;
string td = "7hbgh@jj";

void punch(sockaddr_in sendSockAddr, std::future<void> futureObj) {

    bool yxn = false;
    char msg[1500];
    int i;
    for (i = 0; i < 8; i++) {
        if (futureObj.wait_for(std::chrono::milliseconds(1)) == std::future_status::timeout) {

            //cout << "bang" << endl;
            memset(&msg, 0, sizeof(msg));//clear the buffer
            strcpy(msg, "BANG");
            if (sendto(udpSd, (char*)msg, sizeof(msg), 0, (sockaddr*)&sendSockAddr, sizeof(sendSockAddr)) == -1) {

                cout << "failed to punch" << endl;

            }

            sleep(1);

        }
        else {
            yxn = true;
        }
    }
    if (yxn == false) {
        close(udpSd);
        close(tcpSd);
        yyn = true;
    }
}

sockaddr_in smt() {
    int sock = socket(PF_INET, SOCK_DGRAM, 0);
    sockaddr_in loopback;

    if (sock == -1) {
        std::cerr << "Could not socket\n";
    }

    memset(&loopback, 0, sizeof(loopback));
    loopback.sin_family = AF_INET;
    loopback.sin_addr.s_addr = 1337;   // can be any IP address
    loopback.sin_port = htons(9999);      // using debug port

    if (connect(sock, reinterpret_cast<sockaddr*>(&loopback), sizeof(loopback)) == -1) {
        close(sock);
        std::cerr << "Could not connect\n";
    }

    socklen_t addrlen = sizeof(loopback);
    if (getsockname(sock, reinterpret_cast<sockaddr*>(&loopback), &addrlen) == -1) {
        close(sock);
        std::cerr << "Could not getsockname\n";
    }

    close(sock);

    char buf[INET_ADDRSTRLEN];
    if (inet_ntop(AF_INET, &loopback.sin_addr, buf, INET_ADDRSTRLEN) == 0x0) {
        std::cerr << "Could not inet_ntop\n";
    }
    else {
        std::cout << "Local ip address: " << buf << "\n";
    }

    return loopback;

}

void rcv(int clientSd) {
    char msg[1500];
    while (1)
    {
        //cout << "Awaiting server response..." << endl;
        memset(&msg, 0, sizeof(msg));//clear the buffer
        int a = recv(clientSd, (char*)&msg, sizeof(msg), 0);

        if (a == -1) {
            cout << "cant recv" << endl;
            cout << "lost connection" << endl;
            td = ".lost connection";
            yon = true;
            break;
        }
        if (a == 0) {

            cout << "lost connection" << endl;
            td = "lost connection";
            yon = true;
            break;

        }

        cout << ">someone: " << msg << endl;

        if (!strcmp(msg, "exit"))
        {
            cout << "someone has quit the session" << endl;
            td = "someone has quit the session";
            yon = true;
            break;
        }
        string sr, srr;
        for (int i = 0; i < strlen(msg); i++) {

            sr.push_back(msg[i]);

        }
        srr = ">someone: ";
        td = srr + sr;
        yon = true;
        if ((sr.find(".txt") != std::string::npos) || (sr.find(".doc") != std::string::npos) || (sr.find(".docx") != std::string::npos) ||
            (sr.find(".xlsx") != std::string::npos) || (sr.find(".cpp") != std::string::npos) || (sr.find(".c") != std::string::npos) || (sr.find(".pptx") != std::string::npos)
            || (sr.find(".pdf") != std::string::npos) || (sr.find(".png") != std::string::npos) || (sr.find(".jpg") != std::string::npos))
        {
            cout << "receiving file.." << endl;
            td = "receiving file..";
            yon = true;
            memset(&msg, 0, sizeof(msg));
            recv(clientSd, (char*)&msg, sizeof(msg), 0);
            cout << "size: " << msg << "bytes" << endl;
            int i = 0;
            char* buffer = new char[atoi(msg)];
            while (i < atoi(msg)) {
                const int l = recv(clientSd, &buffer[i], min(4096, atoi(msg) - i), 0);
                if (l < 0) { cout << "bs" << endl; } // this is an error
                i += l;
            }
            cout << "file received " << i << " bytes" << endl;
            td = "file received " + to_string(i) + " bytes";
            yon = true;
            ofstream file(sr, ios::binary);
            file.write(buffer, atoi(msg));
            delete[] buffer;
            file.close();
            cout << "yay" << endl;
            break;
        }
     }

}

void pong() {

    char svmsg[15];
    recv(clientSd, (char*)&svmsg, sizeof(svmsg), 0);
    string sr;
    for (int i = 0; i < strlen(svmsg); i++) {

        sr.push_back(svmsg[i]);

    }
    if (sr.find("PING") != std::string::npos) {

        send(clientSd, (char*)&svmsg, sizeof(svmsg), 0);

    }
}

void SimpleRenderer::sts(const char* st) {
    dt = std::string(st);
    cout << ">me" << dt << endl;
}

const char* SimpleRenderer::rts() {
    const char* a = td.c_str();
    return a;
}

bool SimpleRenderer::yn() {
    bool a = yon;
    return a;
}

void SimpleRenderer::ync() {
    yon = false;
}

void snd(int tcpSd1) {
    char msg[1500];
    string data, hd;
    while (1)
    {

        memset(&msg, 0, sizeof(msg));//clear the buffer

        if (data != dt) {
            data = dt;
            strcpy(msg, (data).c_str());
            if (data == "exit")
            {
                send(tcpSd1, (char*)&msg, strlen(msg), 0);
                break;
            }
            if ((data.find(".txt") != std::string::npos) || (data.find(".doc") != std::string::npos) || (data.find(".docx") != std::string::npos) ||
                (data.find(".xlsx") != std::string::npos) || (data.find(".cpp") != std::string::npos) || (data.find(".c") != std::string::npos) || (data.find(".jpg") != std::string::npos)
                || (data.find(".pptx") != std::string::npos) || (data.find(".pdf") != std::string::npos) || (data.find(".png") != std::string::npos))
            {
                ifstream f1;
                string drtry;
                while (1) {
                    cout << "Directory: ";
                    td = "Directory: ";
                    yon = true;
                    while (1) {
                        if (data == dt) {
                            usleep(50000);
                        }
                        else {
                            break;
                        }
                    }
                    f1.open(dt + data, ios::binary);
                    if (f1.is_open()) {
                        send(tcpSd1, (char*)&msg, strlen(msg), 0);
                        cout << "11" << endl;
                        f1.seekg(0, ios::end);
                        int s1 = f1.tellg();
                        f1.seekg(0, ios::beg);
                        char* buffer = new char[s1];
                        f1.read(buffer, s1);
                        f1.close();
                        memset(&msg, 0, sizeof(msg));
                        strcpy(msg, (to_string(s1)).c_str());
                        send(tcpSd1, (char*)&msg, strlen(msg), 0);
                        usleep(200000);
                        cout << "size: " << msg << endl;
                        int i = 0;
                        while (i < s1) {
                            const int l = send(tcpSd1, &buffer[i], min(4096, s1 - i), 0);
                            if (l < 0) { cout << "bs" << endl; } // this is an error
                            i += l;
                        }
                        delete[] buffer;
                        cout << "file sent " << i << " bytes" << endl;
                        break;
                    }
                    else {
                        cout << "No such file or directory  " << endl;
                        cout << "File name: ";
                        getline(cin, data);
                        if (data == "exit") {
                            break;
                        }
                    }

                }

            }
            else if (send(tcpSd1, (char*)&msg, strlen(msg), 0) == -1) {

                cout << "didn't send through" << endl;
                td = "didn't send through";
                yon = true;
            }

        }
        else {
            usleep(1000);
        }

    }

}

GLuint CompileShader(GLenum type, const std::string& source)
{
    GLuint shader = glCreateShader(type);

    const char* sourceArray[1] = { source.c_str() };
    glShaderSource(shader, 1, sourceArray, NULL);
    glCompileShader(shader);

    GLint compileResult;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);

    if (compileResult == 0)
    {
        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

        std::vector<GLchar> infoLog(infoLogLength);
        glGetShaderInfoLog(shader, (GLsizei)infoLog.size(), NULL, infoLog.data());

        std::string errorMessage = std::string("Shader compilation failed: ");
        errorMessage += std::string(infoLog.begin(), infoLog.end());

        throw std::runtime_error(errorMessage.c_str());
    }

    return shader;
}

GLuint CompileProgram(const std::string& vsSource, const std::string& fsSource)
{
    GLuint program = glCreateProgram();

    if (program == 0)
    {
        throw std::runtime_error("Program creation failed");
    }

    GLuint vs = CompileShader(GL_VERTEX_SHADER, vsSource);
    GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fsSource);

    if (vs == 0 || fs == 0)
    {
        glDeleteShader(fs);
        glDeleteShader(vs);
        glDeleteProgram(program);
        return 0;
    }

    glAttachShader(program, vs);
    glDeleteShader(vs);

    glAttachShader(program, fs);
    glDeleteShader(fs);

    glLinkProgram(program);

    GLint linkStatus;
    glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);

    if (linkStatus == 0)
    {
        GLint infoLogLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

        std::vector<GLchar> infoLog(infoLogLength);
        glGetProgramInfoLog(program, (GLsizei)infoLog.size(), NULL, infoLog.data());

        std::string errorMessage = std::string("Program link failed: ");
        errorMessage += std::string(infoLog.begin(), infoLog.end());

        throw std::runtime_error(errorMessage.c_str());
    }

    return program;
}

SimpleRenderer::SimpleRenderer() :
    mWindowWidth(0),
    mWindowHeight(0),
    mDrawCount(0)
{
    // Vertex Shader source
    const std::string vs = R"(
        uniform mat4 uModelMatrix;
        uniform mat4 uViewMatrix;
        uniform mat4 uProjMatrix;
        attribute vec4 aPosition;
        attribute vec4 aColor;
        varying vec4 vColor;
        void main()
        {
            gl_Position = uProjMatrix * uViewMatrix * uModelMatrix * aPosition;
            vColor = aColor;
        }
    )";

    // Fragment Shader source
    const std::string fs = R"(
        precision mediump float;
        varying vec4 vColor;
        void main()
        {
            gl_FragColor = vColor;
        }
    )";

    // Set up the shader and its uniform/attribute locations.
    mProgram = CompileProgram(vs, fs);
    mPositionAttribLocation = glGetAttribLocation(mProgram, "aPosition");
    mColorAttribLocation = glGetAttribLocation(mProgram, "aColor");
    mModelUniformLocation = glGetUniformLocation(mProgram, "uModelMatrix");
    mViewUniformLocation = glGetUniformLocation(mProgram, "uViewMatrix");
    mProjUniformLocation = glGetUniformLocation(mProgram, "uProjMatrix");

    // Then set up the cube geometry.
    GLfloat vertexPositions[] =
    {
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
    };

    glGenBuffers(1, &mVertexPositionBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexPositionBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);

    GLfloat vertexColors[] =
    {
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f,
    };

    glGenBuffers(1, &mVertexColorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexColorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexColors), vertexColors, GL_STATIC_DRAW);

    short indices[] =
    {
        0, 1, 2, // -x
        1, 3, 2,

        4, 6, 5, // +x
        5, 6, 7,

        0, 5, 1, // -y
        0, 4, 5,

        2, 7, 6, // +y
        2, 3, 7,

        0, 6, 4, // -z
        0, 2, 6,

        1, 7, 3, // +z
        1, 5, 7,
    };

    glGenBuffers(1, &mIndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

SimpleRenderer::~SimpleRenderer()
{
    if (mProgram != 0)
    {
        glDeleteProgram(mProgram);
        mProgram = 0;
    }

    if (mVertexPositionBuffer != 0)
    {
        glDeleteBuffers(1, &mVertexPositionBuffer);
        mVertexPositionBuffer = 0;
    }

    if (mVertexColorBuffer != 0)
    {
        glDeleteBuffers(1, &mVertexColorBuffer);
        mVertexColorBuffer = 0;
    }

    if (mIndexBuffer != 0)
    {
        glDeleteBuffers(1, &mIndexBuffer);
        mIndexBuffer = 0;
    }
}

void SimpleRenderer::Draw()
{
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (mProgram == 0)
        return;

    glUseProgram(mProgram);

    glBindBuffer(GL_ARRAY_BUFFER, mVertexPositionBuffer);
    glEnableVertexAttribArray(mPositionAttribLocation);
    glVertexAttribPointer(mPositionAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, mVertexColorBuffer);
    glEnableVertexAttribArray(mColorAttribLocation);
    glVertexAttribPointer(mColorAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

    MathHelper::Matrix4 modelMatrix = MathHelper::SimpleModelMatrix((float)mDrawCount / 50.0f);
    glUniformMatrix4fv(mModelUniformLocation, 1, GL_FALSE, &(modelMatrix.m[0][0]));

    MathHelper::Matrix4 viewMatrix = MathHelper::SimpleViewMatrix();
    glUniformMatrix4fv(mViewUniformLocation, 1, GL_FALSE, &(viewMatrix.m[0][0]));

    MathHelper::Matrix4 projectionMatrix = MathHelper::SimpleProjectionMatrix(float(mWindowWidth) / float(mWindowHeight));
    glUniformMatrix4fv(mProjUniformLocation, 1, GL_FALSE, &(projectionMatrix.m[0][0]));

    // Draw 36 indices: six faces, two triangles per face, 3 indices per triangle
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
    glDrawElements(GL_TRIANGLES, (6 * 2) * 3, GL_UNSIGNED_SHORT, 0);

    mDrawCount += 1;
}

void SimpleRenderer::SSS(const char* aa, const char* ip) {

    const char* serverIp = ip; int svport = 11111;
    char svmsg[50], svmsg1[50], svmsg2[50], svmsg3[50], svmsg4[50];
    //setup a socket and connection tools 
    struct hostent* svhost = gethostbyname(serverIp);
    sockaddr_in svAddr, sendSockAddr, myAddr;
    bzero((char*)&svAddr, sizeof(svAddr));
    svAddr.sin_family = AF_INET;
    svAddr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr*)*svhost->h_addr_list));
    svAddr.sin_port = htons(svport);

    clientSd = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSd == -1) {
        cout << "cantsocket" << endl;
    }

    if (connect(clientSd, (sockaddr*)&svAddr, sizeof(svAddr)) < 0) {
        cout << "cant connect to server, try again later maybe" << endl;
        td = "cant connect to server, try again later maybe";
        yon = true;
        return;
    }

    td = "..waiting for server";
    yon = true;

    tcpSd = socket(AF_INET, SOCK_STREAM, 0);
    if (tcpSd == -1) {
        cout << "canttcpsocket" << endl;
        return;
    }

    const int opt = 1;
    if (setsockopt(tcpSd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        cout << "prblm" << endl;
    }

    const char* tgtip = aa; char abb[INET_ADDRSTRLEN];
    memset(&svmsg, 0, sizeof(svmsg));//clear the buffer
    strcpy(svmsg, tgtip);
    send(clientSd, (char*)&svmsg, strlen(svmsg), 0);
    memset(&svmsg4, 0, sizeof(svmsg4));
    sockaddr_in fm = smt();
    strcpy(svmsg4, inet_ntop(AF_INET, &(fm.sin_addr.s_addr), abb, INET_ADDRSTRLEN));
    sleep(1);
    send(clientSd, (char*)svmsg4, sizeof(svmsg4), 0);
    bzero((char*)&fm, sizeof(fm));
    int sport; int rport;
    memset(&svmsg1, 0, sizeof(svmsg1));
    memset(&svmsg2, 0, sizeof(svmsg2));
    memset(&svmsg3, 0, sizeof(svmsg3));
    pong();
    int f1, f2, f3;
    f1 = recv(clientSd, (char*)&svmsg1, sizeof(svmsg1), 0);
    if (f1 <= 0) {
        cout << "didntrcv" << endl;
    }
    const char* pt0 = svmsg1;
    cout << svmsg1 << "(bytes:" << f1 << ")" << endl;
    cout << pt0 << endl;


    f2 = recv(clientSd, (char*)&svmsg2, sizeof(svmsg2), 0);
    if (f2 <= 0) {
        cout << "didntrcv" << endl;
    }

    const char* pt = svmsg2;
    cout << svmsg2 << "(bytes:" << f2 << ")" << endl;
    cout << pt << endl;


    f3 = recv(clientSd, (char*)&svmsg3, sizeof(svmsg3), 0);
    if (f3 <= 0) {
        cout << "didntrcv" << endl;
        return;
    }

    const char* pt2 = svmsg3;
    cout << svmsg3 << "(bytes:" << f3 << ")" << endl;
    cout << pt2 << endl;

    //create a message buffer 
    char msg[1500]; sport = atoi(pt); rport = atoi(pt2);
    //setup a socket and connection tools 
    struct hostent* host = gethostbyname(pt0);

    socklen_t ssz = sizeof(sendSockAddr);
    bzero((char*)&sendSockAddr, sizeof(sendSockAddr));
    sendSockAddr.sin_family = AF_INET;
    sendSockAddr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
    sendSockAddr.sin_port = htons(sport);

    bzero((char*)&myAddr, sizeof(myAddr));
    myAddr.sin_family = AF_INET;
    myAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    myAddr.sin_port = htons(rport);

    udpSd = socket(AF_INET, SOCK_DGRAM, 0);
    if (udpSd == -1) {
        cout << "cantsocket" << endl;
        return;
    }

    if (setsockopt(udpSd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        cout << "prblm2" << endl;
    }

    if (::bind(udpSd, (struct sockaddr*)&myAddr, sizeof(myAddr)) < 0) {
        cerr << "cantbind, maybe try another port" << endl;
        td = "cantbind, maybe try another port";
        yon = true;
        return;
    }

    std::promise<void> exitSignal1;
    std::future<void> futureObj1 = exitSignal1.get_future();

    thread t1(&punch, sendSockAddr, std::move(futureObj1));
    cout << "punching.." << endl;
    td = "..connecting";
    yon = true;
    bool flg1 = false;
    bool flg2 = false;
    /*while (1) {
        memset(&msg, 0, sizeof(msg));//clear the buffer
        if (recv(udpSd, (char*)msg, sizeof(msg), 0) != -1) {
            cout << "the other side: " << msg << endl;
            if (!strcmp(msg, "BANG")) {
                cout << "THE HOLE's HERE, telling others.." << endl;
                sendto(udpSd, "WE GOT THE HOLE", 15, 0, (sockaddr*)&sendSockAddr, sizeof(sendSockAddr));
                flg1 = true;
            }
            if (!strcmp(msg, "WE GOT THE HOLE")) {
                cout << "punching done" << endl;
                exitSignal1.set_value();
                t1.join();
                flg2 = true;
            }
            if (flg1 == true && flg2 == true) {
                cout << "hole's ready" << endl;
                break;
            }
        }
        else {
            cout << "cant recv" << endl;
            exitSignal1.set_value();
            t1.join();
            break;
        }
    }*/

    std::thread t2;

    if (::bind(tcpSd, (struct sockaddr*)&myAddr, sizeof(myAddr)) == -1) {
        cout << "cantbindtcp" << endl;
        td = "cantbindtcp";
        yon = true;
        return;
    }

    bool xc = false;

    if (connect(tcpSd, (sockaddr*)&sendSockAddr, sizeof(sendSockAddr)) == -1) {

        cout << errno << endl;
        close(tcpSd);

        if (yyn == false) {
            cout << "cantconnect, retrying once.." << endl;
            usleep(200000);
            for (int i = 0; i < 20; i++) {

                tcptd[i] = socket(AF_INET, SOCK_STREAM, 0);
                if (tcptd[i] == -1) {
                    cout << "canttcpsocket" << endl;
                }

                if (setsockopt(tcptd[i], SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
                    cout << "prblm" << endl;
                }
                if (::bind(tcptd[i], (struct sockaddr*)&myAddr, sizeof(myAddr)) == -1) {
                    cout << "cantbindtcp" << endl;
                    return;
                }
                if (connect(tcptd[i], (sockaddr*)&sendSockAddr, sizeof(sendSockAddr)) == -1 && yyn == false) {

                    cout << "err: " << errno << endl;
                    close(tcptd[i]);
                    usleep(200000);

                }
                else {

                    tcpSd = tcptd[i];
                    xc = true;
                    break;

                }

            }
            if (connect(tcptd[20], (sockaddr*)&sendSockAddr, sizeof(sendSockAddr)) == -1 && yyn == false && xc == false) {
                cout << "cantconnect, retrying twice.." << endl;
                for (int i = 21; i < 200; i++) {

                    tcptd[i] = socket(AF_INET, SOCK_STREAM, 0);
                    if (tcptd[i] == -1) {
                        cout << "canttcpsocket" << endl;
                    }

                    if (setsockopt(tcptd[i], SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
                        cout << "prblm" << endl;
                    }
                    if (::bind(tcptd[i], (struct sockaddr*)&myAddr, sizeof(myAddr)) == -1) {
                        cout << "cantbindtcp" << endl;
                        return;
                    }
                    if (connect(tcptd[i], (sockaddr*)&sendSockAddr, sizeof(sendSockAddr)) == -1 && yyn == false) {

                        cout << errno << endl;
                        close(tcptd[i]);
                        usleep(5000);

                    }
                    else {

                        tcpSd = tcptd[i];
                        xc = true;
                        break;

                    }


                }
                if (yyn == false && xc == false) {
                    cout << "cantconnect, abort" << endl;
                    return;
                }
            }

        }

    }

    if (yyn == false) {

        cout << "hole's ready" << endl;
        exitSignal1.set_value();
        t1.join();
        cout << "connected" << endl;
        td = "connected";
        yon = true;
        string data = "punchedthrough";
        memset(&msg, 0, sizeof(msg));//clear the buffer
        strcpy(msg, (data).c_str());
        send(clientSd, (char*)&msg, strlen(msg), 0);
        memset(&msg, 0, sizeof(msg));//clear the buffer
        close(clientSd);

    }
    else {

        t1.join();
        cout << "relaying" << endl;
        td = "relaying";
        yon = true;
        string data = "punchedfail";
        memset(&msg, 0, sizeof(msg));//clear the buffer
        strcpy(msg, (data).c_str());
        send(clientSd, (char*)&msg, strlen(msg), 0);
        memset(&msg, 0, sizeof(msg));//clear the buffer
        close(tcpSd);
        tcpSd = clientSd;

    }

    t2 = std::thread(rcv, tcpSd);
    snd(tcpSd);
    t2.join();

    close(tcpSd);

    close(udpSd);
    cout << "********Session********" << endl;
    cout << "Connection closed" << endl;
    td = "********Session********\nConnection closed";
    yon = true;
}

void SimpleRenderer::UpdateWindowSize(GLsizei width, GLsizei height)
{
    glViewport(0, 0, width, height);
    mWindowWidth = width;
    mWindowHeight = height;
}
