# Arduino ESP8266 天猫精灵控制模块

## 说明

时间仓促, 只支持一些简单的配置请求

## 功能

✔ 通过贝壳物联网连接到天猫精灵, 通过天猫精灵控制  
✔ 连接到自定义服务器  
✔ 自动重连机制  
✔ 客户端主动心跳  
✔ 批量远程更新  

## 简单使用

### 1. 配网

  上电后, 连接到 `ESP8266` 的 `AP` (WiFi样式 ESP8266_XXXXXX), 使用下面方法进行 `Station` 的连接:

```javascript
ip:port/changeWlan?ssid=[ssid]&password=[password]
// eg: 192.168.128.1/changeWlan?ssid=r3inbowari&password=1008611
```
  
### 2. 配置自定义服务器
  
  使用下面的命令进行自定义服务器的设置

```javascript
ip:port/changeHost?host=[host]&port=[port]
```

### 3. 配置贝壳物联网连接到天猫

  使用下面的命令设置

```javascript
ip:port/changeIOT?host=[host]&port=[port]
```

### 4. 配置贝壳物联网权限 `APIKEY(appid)` 和设备 `ID`

   使用下面的命令设置

```javascript
ip:port/changeAuth?id=[id]&appid=[appid]
```

## 注意事项

### 1. AP模式下的默认网关为 `192.168.128.1`

### 2. 所有的配置请求方法均为 `GET`, 请求端口均为 `80`
