# 5_IRC_Serv

## Description

This project consists of developing an IRC (Internet Relay Chat) server compliant with the IRC protocol specifications. The goal is to allow multiple clients to connect, join channels, exchange messages, and interact using standard IRC commands.

## 🚀 Features

- Handle multiple simultaneous client connections
- Create and manage public and private chat channels
- Implement IRC commands (JOIN, PART, PRIVMSG, NICK...)
- Manage users, nicknames, and access rights
- Private messaging between users

## 📦 Requirements

- Operating System: Linux or macOS
- C++ compiler compatible with C++98 standard

## ⚙️ Installation

1. Clone the repository:

```
git clone https://github.com/qbnt/5_IRC_Serv.git
cd 5_IRC_Serv
```

2. Compile the project:

```
make
```

## 💡 Usage

- Launch the server:

```
./irc_server <port> <password>
```

- Connect with an IRC client:
  - Host: `localhost` or server IP address
  - Port: The port you specified when launching the server
  - Password: The password you specified

- Basic commands:
  - Join a channel: `/join #channel_name`
  - Private message: `/msg nickname message`
  - Change nickname: `/nick new_nickname`

## 📄 License

Project licensed under the MIT License. See [LICENSE](LICENSE).
