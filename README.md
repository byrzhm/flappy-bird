# 2023·计算机图形学与三维游戏引擎开发·期末作业

## 程序依赖

- `SFML 2.6.1`
- `nlohmann`
- `glm`
- `cmake >= 3.10`
- `git`

## 编译(仅限windows平台下使用vscode编译的情况)

- 首先确保已经安装了`cmake`, `vscode`, `vcpkg` 以及 `git`
- 保证程序依赖已经安装, 如果没有安装, 可以使用以下指令安装(确保环境变量已经配置好)

```bash
vcpkg install sfml:x64-windows
vcpkg install glm:x64-windows
vcpkg integrate install
```

- 在vscode中安装`CMake Tools`, 并且在当前工作目录下的`.vscode`文件夹下的`settings.json`中添加以下内容\
  如果`intelisense`或`clangd`报错, 可以尝试添加`include`路径

```json
{
    "cmake.configureSettings": {
        "CMAKE_TOOLCHAIN_FILE": "${env:VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake",
        "VCPKG_TARGET_TRIPLET": "x64-windows",
    }
}
```

- 使用`CMake Tools`进行配置构建, 注意要选择MSVC编译器(这是因为ABI的问题)

## 运行

- 在`build`文件夹下找到`Debug`/`Release`文件夹, 运行`flappy_bird.exe`即可(如果运行没有效果, 可能是缺失了dll文件, 或者是缺失了settings.json中的配置以及assets文件夹)

## 游戏说明

- 点击鼠标左键控制小鸟飞行
- 按下`R`键可以重新开始游戏
- 当小鸟飞过一个管道时, 得一分
- 当小鸟撞到管道时, 游戏结束

## 游戏截图

![Screenshot 2023-12-08 203139.png](README.assets/Screenshot%202023-12-08%20203139.png)
