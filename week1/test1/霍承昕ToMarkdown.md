# 霍承昕toMarkDown

## git组成

### 储存

Git Object 共有4种，blob、tree、commit、tag。

1. blob 类型仅负责储存一个文件的内容，不包括文件名等其他信息。然后将这些信息经过SHA1哈希算法得到对应的哈希值作为这个object在Git仓库中的唯一身份证。
2. tree 类型将目录结构打了一个快照。它储存了一个目录结构（类似于文件夹），以及每一个文件（或者子文件夹）的权限、类型、对应的身份证（SHA1值）、以及文件名。
3. commit 储存的是一个提交的信息，包括对应目录结构的快照tree的哈希值，上一个提交的哈希值，提交的作者以及提交的具体时间，最后是该提交的信息。
4. tag 是一个"固化的分支"，一旦打上 tag 之后，这个 tag 代表的内容将永远不可变，因为 tag 只会关联当时版本库中最后一个 commit 对象。

### 分区

git 共有3个分区，分别为working directory，index or staging area，git repository。

1. working directory (工作目录):操作系统上的文件，所有代码开发编辑都在这上面完成。
2. index or staging area (索引):可以理解为一个暂存区域，这里面的代码会在下一次commit被提交到Git仓库。
3. git repository (Git仓库):由Git object记录着每一次提交的快照，以及链式结构记录的提交变更历史。

## git 命令

![git command](git-command.jpg "git command")
