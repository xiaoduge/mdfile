###   1、创建版本库  

mkdir repositoryName
cd repositoryName
pwd     //用于显示当前目录
git init  //把这个目录变成Git可以管理的仓库

### 2、添加文件到版本库

git add <filename>
git commit -m "file message"

### 3、提交修改

git status       // 查看状态
git diff <filename>    //查看工作区和版本库里面最新版本的区别
git add <filename>      //把文件保存到暂存区
git commit -m "file message"   //把暂存区的内容提交到当前分支

### 4、版本退回

git log     //查看版本信息,查看commit_id
git reset --hard HEAD^    //返回上一版本
//HEAD为当前版本，HEAD^为上一版本，HEAD^^为上上版本，往上100个版本可写成HEAD~100
git reset --hard commit_id;  //返回到指定commit_id版本
git reflog    //记录命令

### 5、撤销修改

git checkout -- fileName //改乱了工作区的内容，想直接丢弃工作区的修改时使用
git reset HEAD fileName  //把暂存区的修改撤销掉，重新返回工作区。当不但改乱了工作区的内容，还添加到暂存区时，想丢弃修改，先git reset HEAD fileName 然后 git checkout -- fileName
//已经提交到版本库，可直接版本退回

### 6、删除

//当文件删除后，需要从版本库中删除
git rm <fileName>
//误删文件后，在没有执行git rm <fileName>前可以使用，命令git checkout -- <fileName>恢复文件

### 7、远程版本库

第一步：注册github账户
第二步：创建SSH Key。在用户主目录下看看有没有.ssh目录,若有再看看目录下有无id_rsa（私钥）和id_rsa.pub（公钥）这两个文件。若没有，则执行命令 ssh-keygen -t rsa -C "youremail@example.com"
第三步：登录GitHub，"setting" " SSH Keys" 添加SSH Key，填上任意Title，在Key文本框里粘贴id_rsa.pub文件的内容。
第四步：登录GitHub建立 repository，在本地执行命令：git remote add origin git@github.com:<userName>/<repositoryName.git>
第五步:
git push -u origin master   //把本地库推送到远程库，第一次推送时加上了-u参数，Git不但会把本地的master分支内容推送的远程新的master分支，还会把本地的master分支和远程的master分支关联起来，在以后的推送或者拉取时就可以简化命令
git push origin master   //之后可以不见-u参数，直接推送
git push origin developName  //提交分支

git push origin :devName   //删除github上的远程分支
git pull [远程仓库名][分支名] //后面两个默认为origin master；从远程仓库把代码取下来，将其他人的代码提交的代码同步到本地

git clone git@github.com:<userName>/<repoName.git>

git remote remove origin   //删除远程连接

### 8、分支管理

创建与合并分支：
git checkout -b <developName>  //创建并切换，相当于以下两条指令
git branch <developName>  //创建
git checkout <developName>  //切换
git branch   //查看当前分支 *表示当前分支

git checkout master //切换回master分支
git merge <developName>  //切换到master分支后，将<developName>分支合并到master。
git branch -d <developName>  //删除分支。

分支管理策略：
Fast forward模式，删除分支后，会丢掉分支信息
No Fast Forward模式，Git会在merge时生产一个新的commit,这样从分支历史上就可以看出分支信息，命令：
git merge --no-ff -m "commit message" <devName>

BUG分支：
stash“储藏功能”:
git stash    //第一步将工作区存储
git status   //查看工作区，应该是干净的
git checkout master   //切换到master分支
git checkout -b <developName>  //在master分支上创建分支<developName>，并切换到新建分支
//修改bug
git add <fileName>  //将修改bug后的文件保存到暂存区
git commit -m "commit message"  //提交暂存区的内容
git checkout master   //切换到master分支
git merge --no-ff -m "commit message" <developName>  //按--no-ff的策略合并分支
git branch -d <developName>  //  删除分支<developName>
git checkout <wordDevelopName>  // 切换到之前的工作分支
git status       //查看工作分支状态，应该是干净的
git stash list    //查看存储列表，可以看到之前存储的工作现场
//恢复工作现场方法一
git stash apply   //恢复现场，但stash内容不删除
git stash drop    //删除存储的现场
//恢复工作现场方法二
git stash pop    //恢复现场并删除
git stash list    //查看存储列表，应该为空
//若存储了多个工作现场，可使用以下命令恢复
git stash apply stash@{0}  //stash@{0}为现场编号

git branch -D <developName> //强行删除分支

### 9、标签管理

git tag <tagName>  //创建标签
git tag <tagName> <commit_id>  //根据commit_id创建标签
git tag    //查看标签
git show <tagName>   //查看标签信息
git log --pretty=oneline --abbrev-commit
git tag -a <tagName> -m "version message" <commit_id> //创建带说明的标签
git tag -d <tagName>  //删除标签
git push origin :refs/tags/<tagName>
git push origin <tagName> //推送某个标签到远程
git push origin --tags   //推送全部尚未推送的本地标签








