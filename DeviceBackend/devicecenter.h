#ifndef DEVICECENTER_H
#define DEVICECENTER_H

#include <QQuickItem>
#include <QThread>
#include <QJsonArray>
#include <QTcpSocket>
#include <QModbusClient>
#include <QModbusTcpClient>
#include <QList>
#include <QMap>
#include <QTimer>
#include <QRunnable>
#include <QThreadPool>
#include <QWebEnginePage>

#include "devicelineno.h"
#include "devicescanner.h"
#include "deviceplc.h"
#include "devicerobot.h"
#include "centworker/scannerworker.h"
#include "centworker/plcworker.h"
#include "centworker/robotworker.h"
#include "centworker/schedulingworker.h"
#include "worker/httpaddlogworker.h"
#include "worker/hdatetimeworker.h"
#include "struct/hdatetime.h"


/*
    @brief 在该类中处理所有的设备逻辑; 启动与停止, 以及生命周期由前端管理
*/
class DeviceCenter : public QQuickItem
{
    Q_OBJECT
    QML_ELEMENT
public:
    DeviceCenter();
    ~DeviceCenter();

    ScannerWorker* findScannerWorker(DeviceLineNo line);
    RobotWorker* findRobotWorker(DeviceLineNo line);
    PlcWorker* findPlcWorker(DeviceLineNo line);

#pragma region "设备启动以及生命周期相关相关 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" {
    // @brief 开始处理设备逻辑
    Q_INVOKABLE void start();
    // @brief 停止处理设备逻辑
    Q_INVOKABLE void stop();
#pragma endregion }

#pragma region "控制设备相关 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" {
    // @brief 连接扫码枪
    Q_INVOKABLE void addscanner(int dId, QString ip, int port, DeviceLineNo lineNo);

    // @brief 连接机器人
    Q_INVOKABLE void addrobot(int dId, QString ip, int port, DeviceLineNo lineNo);

    // @brief 连接PLC
    Q_INVOKABLE void addplc(int dId, QString ip, int port, DeviceLineNo lineNo, QList<int> allowLines);

    // @brief 订阅调度服务
    Q_INVOKABLE void addscheduling(int dId, QString ip, int port, DeviceLineNo lineNo);

    /*
        @brief 基于指定设备一个新的连接参数
        @param deviceType - GlobalEnums.DeviceType
    */
    Q_INVOKABLE void reconnect(int dId, QString ip, int port);
#pragma endregion }

#pragma region "其他实用函数 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" {
    Q_INVOKABLE void appendLog(QString url, QString content, int level);
    // TODO: implement
    // Q_INVOKABLE QDateTime progTime();
#pragma endregion }

private:
    QMap<int, DeviceScanner*> scannerList;
    QMap<int, ScannerWorker*> scannerWorkers;   // worker is automatically deleted after use
    QMap<int, DevicePLC*> plcList;
    QMap<int, PlcWorker*> plcWorkers;   // worker is automatically deleted after use
    QMap<int, DeviceRobot*> robotList;
    QMap<int, RobotWorker*> robotWorkers;   // worker is automatically deleted after use
    QMap<int, SchedulingWorker*> schedulingWorkers;
    QMap<int, QThread*> workerThreads;  // thread is automatically deleted after use
    bool running = false;
    HttpAddLogWorker *logWorker = nullptr;
    HDateTimeWorker *utcThread = nullptr;

#pragma region "路径计算脚本+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" {
    QString easystar = "var EasyStar=function(e){var o={};function r(t){if(o[t])return o[t].exports;var n=o[t]={i:t,l:!1,exports:{}};return e[t].call(n.exports,n,n.exports,r),n.l=!0,n.exports}return r.m=e,r.c=o,r.d=function(t,n,e){r.o(t,n)||Object.defineProperty(t,n,{enumerable:!0,get:e})},r.r=function(t){\"undefined\"!=typeof Symbol&&Symbol.toStringTag&&Object.defineProperty(t,Symbol.toStringTag,{value:\"Module\"}),Object.defineProperty(t,\"__esModule\",{value:!0})},r.t=function(n,t){if(1&t&&(n=r(n)),8&t)return n;if(4&t&&\"object\"==typeof n&&n&&n.__esModule)return n;var e=Object.create(null);if(r.r(e),Object.defineProperty(e,\"default\",{enumerable:!0,value:n}),2&t&&\"string\"!=typeof n)for(var o in n)r.d(e,o,function(t){return n[t]}.bind(null,o));return e},r.n=function(t){var n=t&&t.__esModule?function(){return t.default}:function(){return t};return r.d(n,\"a\",n),n},r.o=function(t,n){return Object.prototype.hasOwnProperty.call(t,n)},r.p=\"/bin/\",r(r.s=0)}([function(t,n,e){var P={},M=e(1),_=e(2),A=e(3);t.exports=P;var E=1;P.js=function(){var c,i,f,s=1.4,p=!1,u={},o={},r={},l={},a=!0,h={},d=[],y=Number.MAX_VALUE,v=!1;this.setAcceptableTiles=function(t){t instanceof Array?f=t:!isNaN(parseFloat(t))&&isFinite(t)&&(f=[t])},this.enableSync=function(){p=!0},this.disableSync=function(){p=!1},this.enableDiagonals=function(){v=!0},this.disableDiagonals=function(){v=!1},this.setGrid=function(t){c=t;for(var n=0;n<c.length;n++)for(var e=0;e<c[0].length;e++)o[c[n][e]]||(o[c[n][e]]=1)},this.setTileCost=function(t,n){o[t]=n},this.setAdditionalPointCost=function(t,n,e){void 0===r[n]&&(r[n]={}),r[n][t]=e},this.removeAdditionalPointCost=function(t,n){void 0!==r[n]&&delete r[n][t]},this.removeAllAdditionalPointCosts=function(){r={}},this.setDirectionalCondition=function(t,n,e){void 0===l[n]&&(l[n]={}),l[n][t]=e},this.removeAllDirectionalConditions=function(){l={}},this.setIterationsPerCalculation=function(t){y=t},this.avoidAdditionalPoint=function(t,n){void 0===u[n]&&(u[n]={}),u[n][t]=1},this.stopAvoidingAdditionalPoint=function(t,n){void 0!==u[n]&&delete u[n][t]},this.enableCornerCutting=function(){a=!0},this.disableCornerCutting=function(){a=!1},this.stopAvoidingAllAdditionalPoints=function(){u={}},this.findPath=function(t,n,e,o,r){function i(t){p?r(t):setTimeout(function(){r(t)})}if(void 0===f)throw new Error(\"You can't set a path without first calling setAcceptableTiles() on EasyStar.\");if(void 0===c)throw new Error(\"You can't set a path without first calling setGrid() on EasyStar.\");if(t<0||n<0||e<0||o<0||t>c[0].length-1||n>c.length-1||e>c[0].length-1||o>c.length-1)throw new Error(\"Your start or end point is outside the scope of your grid.\");if(t!==e||n!==o){for(var s=c[o][e],u=!1,l=0;l<f.length;l++)if(s===f[l]){u=!0;break}if(!1!==u){var a=new M;a.openList=new A(function(t,n){return t.bestGuessDistance()-n.bestGuessDistance()}),a.isDoneCalculating=!1,a.nodeHash={},a.startX=t,a.startY=n,a.endX=e,a.endY=o,a.callback=i,a.openList.push(O(a,a.startX,a.startY,null,1));o=E++;return h[o]=a,d.push(o),o}i(null)}else i([])},this.cancelPath=function(t){return t in h&&(delete h[t],!0)},this.calculate=function(){if(0!==d.length&&void 0!==c&&void 0!==f)for(i=0;i<y;i++){if(0===d.length)return;p&&(i=0);var t=d[0],n=h[t];if(void 0!==n)if(0!==n.openList.size()){var e=n.openList.pop();if(n.endX!==e.x||n.endY!==e.y)(e.list=0)<e.y&&T(n,e,0,-1,+b(e.x,e.y-1)),e.x<c[0].length-1&&T(n,e,1,0,+b(e.x+1,e.y)),e.y<c.length-1&&T(n,e,0,1,+b(e.x,e.y+1)),0<e.x&&T(n,e,-1,0,+b(e.x-1,e.y)),v&&(0<e.x&&0<e.y&&(a||g(c,f,e.x,e.y-1,e)&&g(c,f,e.x-1,e.y,e))&&T(n,e,-1,-1,s*b(e.x-1,e.y-1)),e.x<c[0].length-1&&e.y<c.length-1&&(a||g(c,f,e.x,e.y+1,e)&&g(c,f,e.x+1,e.y,e))&&T(n,e,1,1,s*b(e.x+1,e.y+1)),e.x<c[0].length-1&&0<e.y&&(a||g(c,f,e.x,e.y-1,e)&&g(c,f,e.x+1,e.y,e))&&T(n,e,1,-1,s*b(e.x+1,e.y-1)),0<e.x&&e.y<c.length-1&&(a||g(c,f,e.x,e.y+1,e)&&g(c,f,e.x-1,e.y,e))&&T(n,e,-1,1,s*b(e.x-1,e.y+1)));else{var o=[];o.push({x:e.x,y:e.y});for(var r=e.parent;null!=r;)o.push({x:r.x,y:r.y}),r=r.parent;o.reverse(),n.callback(o),delete h[t],d.shift()}}else n.callback(null),delete h[t],d.shift();else d.shift()}};var T=function(t,n,e,o,r){e=n.x+e,o=n.y+o;void 0!==u[o]&&void 0!==u[o][e]||!g(c,f,e,o,n)||(void 0===(o=O(t,e,o,n,r)).list?(o.list=1,t.openList.push(o)):n.costSoFar+r<o.costSoFar&&(o.costSoFar=n.costSoFar+r,o.parent=n,t.openList.updateItem(o)))},g=function(t,n,e,o,r){var i=l[o]&&l[o][e];if(i){var s=x(r.x-e,r.y-o);if(!function(){for(var t=0;t<i.length;t++)if(i[t]===s)return!0;return!1}())return!1}for(var u=0;u<n.length;u++)if(t[o][e]===n[u])return!0;return!1},x=function(t,n){if(0===t&&-1===n)return P.TOP;if(1===t&&-1===n)return P.TOP_RIGHT;if(1===t&&0===n)return P.RIGHT;if(1===t&&1===n)return P.BOTTOM_RIGHT;if(0===t&&1===n)return P.BOTTOM;if(-1===t&&1===n)return P.BOTTOM_LEFT;if(-1===t&&0===n)return P.LEFT;if(-1===t&&-1===n)return P.TOP_LEFT;throw new Error(\"These differences are not valid: \"+t+\", \"+n)},b=function(t,n){return r[n]&&r[n][t]||o[c[n][t]]},O=function(t,n,e,o,r){if(void 0!==t.nodeHash[e]){if(void 0!==t.nodeHash[e][n])return t.nodeHash[e][n]}else t.nodeHash[e]={};var i=m(n,e,t.endX,t.endY),r=null!==o?o.costSoFar+r:0,i=new _(o,n,e,r,i);return t.nodeHash[e][n]=i},m=function(t,n,e,o){var r,i;return v?(r=Math.abs(t-e))<(i=Math.abs(n-o))?s*r+i:s*i+r:(r=Math.abs(t-e))+(i=Math.abs(n-o))}},P.TOP=\"TOP\",P.TOP_RIGHT=\"TOP_RIGHT\",P.RIGHT=\"RIGHT\",P.BOTTOM_RIGHT=\"BOTTOM_RIGHT\",P.BOTTOM=\"BOTTOM\",P.BOTTOM_LEFT=\"BOTTOM_LEFT\",P.LEFT=\"LEFT\",P.TOP_LEFT=\"TOP_LEFT\"},function(t,n){t.exports=function(){this.pointsToAvoid={},this.startX,this.callback,this.startY,this.endX,this.endY,this.nodeHash={},this.openList}},function(t,n){t.exports=function(t,n,e,o,r){this.parent=t,this.x=n,this.y=e,this.costSoFar=o,this.simpleDistanceToTarget=r,this.bestGuessDistance=function(){return this.costSoFar+this.simpleDistanceToTarget}}},function(t,n,e){t.exports=e(4)},function(u,T,t){var g,x;(function(){var t,p,l,h,d,n,a,e,y,v,o,r,i,c,f;function s(t){this.cmp=null!=t?t:p,this.nodes=[]}l=Math.floor,v=Math.min,p=function(t,n){return t<n?-1:n<t?1:0},y=function(t,n,e,o,r){var i;if(null==e&&(e=0),null==r&&(r=p),e<0)throw new Error(\"lo must be non-negative\");for(null==o&&(o=t.length);e<o;)r(n,t[i=l((e+o)/2)])<0?o=i:e=i+1;return[].splice.apply(t,[e,e-e].concat(n)),n},n=function(t,n,e){return null==e&&(e=p),t.push(n),c(t,0,t.length-1,e)},d=function(t,n){var e,o;return null==n&&(n=p),e=t.pop(),t.length?(o=t[0],t[0]=e,f(t,0,n)):o=e,o},e=function(t,n,e){var o;return null==e&&(e=p),o=t[0],t[0]=n,f(t,0,e),o},a=function(t,n,e){var o;return null==e&&(e=p),t.length&&e(t[0],n)<0&&(n=(o=[t[0],n])[0],t[0]=o[1],f(t,0,e)),n},h=function(e,t){var n,o,r,i,s,u;for(null==t&&(t=p),s=[],o=0,r=(i=function(){u=[];for(var t=0,n=l(e.length/2);0<=n?t<n:n<t;0<=n?t++:t--)u.push(t);return u}.apply(this).reverse()).length;o<r;o++)n=i[o],s.push(f(e,n,t));return s},i=function(t,n,e){if(null==e&&(e=p),-1!==(n=t.indexOf(n)))return c(t,0,n,e),f(t,n,e)},o=function(t,n,e){var o,r,i,s,u;if(null==e&&(e=p),!(r=t.slice(0,n)).length)return r;for(h(r,e),i=0,s=(u=t.slice(n)).length;i<s;i++)o=u[i],a(r,o,e);return r.sort(e).reverse()},r=function(t,n,e){var o,r,i,s,u,l,a,c,f;if(null==e&&(e=p),10*n<=t.length){if(!(i=t.slice(0,n).sort(e)).length)return i;for(r=i[i.length-1],s=0,l=(a=t.slice(n)).length;s<l;s++)e(o=a[s],r)<0&&(y(i,o,0,null,e),i.pop(),r=i[i.length-1]);return i}for(h(t,e),f=[],u=0,c=v(n,t.length);0<=c?u<c:c<u;0<=c?++u:--u)f.push(d(t,e));return f},c=function(t,n,e,o){var r,i,s;for(null==o&&(o=p),r=t[e];n<e&&o(r,i=t[s=e-1>>1])<0;)t[e]=i,e=s;return t[e]=r},f=function(t,n,e){var o,r,i,s,u;for(null==e&&(e=p),r=t.length,i=t[u=n],o=2*n+1;o<r;)(s=o+1)<r&&!(e(t[o],t[s])<0)&&(o=s),t[n]=t[o],o=2*(n=o)+1;return t[n]=i,c(t,u,n,e)},s.push=n,s.pop=d,s.replace=e,s.pushpop=a,s.heapify=h,s.updateItem=i,s.nlargest=o,s.nsmallest=r,s.prototype.push=function(t){return n(this.nodes,t,this.cmp)},s.prototype.pop=function(){return d(this.nodes,this.cmp)},s.prototype.peek=function(){return this.nodes[0]},s.prototype.contains=function(t){return-1!==this.nodes.indexOf(t)},s.prototype.replace=function(t){return e(this.nodes,t,this.cmp)},s.prototype.pushpop=function(t){return a(this.nodes,t,this.cmp)},s.prototype.heapify=function(){return h(this.nodes,this.cmp)},s.prototype.updateItem=function(t){return i(this.nodes,t,this.cmp)},s.prototype.clear=function(){return this.nodes=[]},s.prototype.empty=function(){return 0===this.nodes.length},s.prototype.size=function(){return this.nodes.length},s.prototype.clone=function(){var t=new s;return t.nodes=this.nodes.slice(0),t},s.prototype.toArray=function(){return this.nodes.slice(0)},s.prototype.insert=s.prototype.push,s.prototype.top=s.prototype.peek,s.prototype.front=s.prototype.peek,s.prototype.has=s.prototype.contains,s.prototype.copy=s.prototype.clone,t=s,g=[],void 0===(x=\"function\"==typeof(x=function(){return t})?x.apply(T,g):x)||(u.exports=x)}).call(this)}]);\r\n";
    QString script = R"(
var paths = [];
var easystar = new EasyStar.js();
var grid = {grid};
easystar.setGrid(grid);
easystar.setAcceptableTiles([0]);
easystar.enableSync();
easystar.findPath(startX, startY, endX, endY, function( path ) {
    if (path === null) {
        paths = [];
    } else {
        paths = path;
    }
});
easystar.setIterationsPerCalculation(1000);
easystar.calculate();
)";
#pragma endregion }

    void main();    // 主函数, 用于启动各类设置
    void loop();    // 任务主循环

public slots:
    // @brief 收到来自扫码枪的条码
    void scannerReceived(DeviceScanner*, QString barcode);
    // @brief 扫码枪已连接
    void scannerConnected(DeviceScanner*);
    // @brief 扫码枪连接失败
    void scannerConnectFailed(DeviceScanner*);
    // @brief 扫码枪已断开连接
    void scannerDisconnected(DeviceScanner*);
    // @brief 扫码枪查询条码失败
    void scannerQueryFailed(DeviceScanner*, QString barcode, QJsonObject result, long cost);
    // @brief 扫码枪查询条码成功
    void scannerQuerySuccess(DeviceScanner*, QString barcode, QJsonObject result, long cost);
    // @brief 扫码结果产品流向正常线
    void scannerGotoNormal(DeviceScanner*, DeviceLineNo, QString barcode);
    // @brief 扫码结果产品流向异常线
    void scannerGotoError(DeviceScanner*, DeviceLineNo, QString barcode);
    // @brief 扫码结果即将换产
    void scannerGotoChange(DeviceScanner*, DeviceLineNo, QString orderNo, int len, int wide, int height);
    // @brief 发起了机器人已码垛请求, 但是未找到当前线体已扫码的物料
    void scannerNoAvailableStack(DeviceScanner*);
    // @brief 物料已上传且加入到码垛中
    void scannerPullUped(DeviceScanner*, DeviceLineNo, QString barcode);
    // @breif 物料扫码已确认
    void scannerUploaded(DeviceScanner*, DeviceLineNo, QString barcode);
    // @brief 允许指定线体出板
    void scannerApproveOut(DeviceScanner*, DeviceLineNo);
    // @brief 拒绝指定线体出板
    void scannerRejectOut(DeviceScanner*, DeviceLineNo);
    // @brief 发送扫码枪心跳数据
    void scannerSendedKeep(DeviceScanner*, QString);
    // @breif 准备换产
    void scannerChangeReady(DeviceScanner*, DeviceLineNo);
    // @brief PLC连接成功时
    void plcConnected(DevicePLC*);
    // @brief PLC断开连接或连接失败时
    void plcDisconnected(DevicePLC*);
    // @brief on PLC TX
    void _plcTx(DevicePLC*);
    // @brief on PLC RX
    void _plcRx(DevicePLC*);
    // @breif PLC register writed
    void _plcWrited(DevicePLC*, int addr, ushort value);
    // @brief 指定线体机器人已码好
    void _plcPullUp(DevicePLC*, DeviceLineNo);
    // @brief 指定线体PLC在一定秒数内重复发起夹料完成
    void _plcDuplicateClamped(DevicePLC*, DeviceLineNo, long);
    // @brief 发送内容到机器人
    void _robotSended(DeviceRobot*, QString content);
    // @brief 收到来自机器人的响应
    void _robotReceived(DeviceRobot*, QString content);
    // @brief 长时间未收到机器人心跳数据, 应当重新连接
    void _robotHeartStopped(DeviceRobot*);
    // @brief 机器人已连接
    void robotConnected(DeviceRobot*);
    // @brief 机器人连接失败
    void robotConnectFailed(DeviceRobot*);
    // @brief 机器人已断开连接
    void robotDisconnected(DeviceRobot*);
    // @brief on Robot TX
    void _robotTx(DeviceRobot*);
    // @brief on Robot RX
    void _robotRx(DeviceRobot*);
    // @breif on Scheduling Connected
    void _schedulingConnected(SchedulingWorker*);
    // @breif on Scheduling Disconnected
    void _schedulingDisconnected(SchedulingWorker*);
    // @brief on Scheduling Task Tx
    void _schedulingTx(SchedulingWorker*);
    // @breif on Scheduling Task Rx
    void _schedulingRx(SchedulingWorker*);

    void received() { qDebug() << "received"; }

signals:
    // @brief 当 DeviceCenter 启动时
    void started();
    // @brief 当 DeviceCenter 停止时
    void stoped();
    // @breif
    void _appendLog(QString url, QString content, int level);
    // @brief 当某个设备连接成功时
    void deviceConnected(int dId);
    // @brief 当某个设备断开连接时
    void deviceDisconnect(int dId);
    // @brief 当某个设备重新应用了新的连接参数时
    void deviceApplied(int dId, QString ip, int port);
    // @biref 当某个设备连接失败时
    void deviceConnectFailed(int dId);
    // @breif 当扫码枪接收到条码时
    void barcodeReceived(int dId, QString barcode);
    // @brief 当条码查询失败时
    void barcodeQueryFailed(int dId, QString barcode, QJsonObject result, long cost);
    // @brief 当条码查询成功时
    void barcodeQuerySuccess(int dId, QString barcode, QJsonObject result, long cost);
    // @brief 扫码结果产品流向正常线
    void barcodeGotoNormal(int dId, QString barcode);
    // @brief 扫码结果产品流向异常线
    void barcodeGotoError(int dId, QString barcode);
    // @brief 扫码结果产品流向异常线
    void barcodeGotoChange(int dId, int line, QString orderNo, int len, int wide, int height);
    // @brief 发起了机器人已码垛请求, 但是未找到当前线体已扫码的物料
    void barcodeNoAvailableStack(int dId);
    // @brief 物料已上传且加入到码垛中
    void barcodePullUped(int dId, QString barcode);
    // @breif 物料扫码已确认
    void barcodeUploaded(int dId, QString barcode);
    // @brief 允许指定线体出板
    void barcodeApproveOut(int dId);
    // @brief 拒绝指定线体出板
    void barcodeRejectOut(int dId);
    // @breif 已向扫码枪发送心跳指令
    void barcodeSendedKeep(int dId, QString cmd);
    // @breif 准备换产
    void barcodeChangeReady(int dId);
    // @brief on PLC TX
    void plcTx(int dId);
    // @brief on PLC RX
    void plcRx(int dId);
    // @brief plc register writed
    void plcWrited(int dId, int addr, int value);
    // @breif 指定线体机器人已码好
    void plcPullUp(int dId, int line);
    // @brief 指定线体PLC在一定秒数内重复发起夹料完成
    void plcDuplicateClamped(int dId, int line, long diff);
    // @breif 当向机器人发送内容时
    void robotSended(int dId, QString content);
    // @breif 当机器人返回内容时
    void robotReceived(int dId, QString content);
    // @brief 当长时间未收到机器人心跳数据, 应当重新连接
    void robotHeartStopped(int dId);
    // @brief on Robot TX
    void robotTx(int dId);
    // @brief on Robot RX
    void robotRx(int dId);
    // @brief on Scheduling Task Tx
    void schedulingTx(int dId);
    // @brief on Scheduling Task Rx
    void schedulingRx(int dId);
};

#endif // DEVICECENTER_H
