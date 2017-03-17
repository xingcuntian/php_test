
count=`ps -fe |grep "redis" | grep -v "grep" | wc -l`
if [ $count -lt 1 ]; then
   ps -eaf |grep "redis" | grep -v "grep"| awk '{print $2}'|xargs kill -9
   sleep 1
   ulimit -c unlimited
   /etc/init.d/redis start
echo "restart";
echo $(date +%Y-%m-%d_%H:%M:%S) >/tmp/restart.log
fi

counts=`ps -fe |grep "httpd" | grep -v "grep" | wc -l`
if [ $counts -lt 2 ]; then
    ps -eaf |grep "httpd" | grep -v "grep"| awk '{print $2}'|xargs kill -9
    sleep 1
    ulimit -c unlimited
    deadPID=`/etc/init.d/httpd start | tr -cd [0-9]` 
    kill -9 $deadPID | /etc/init.d/httpd start  
echo "restart";
echo $(date +%Y-%m-%d_%H:%M:%S) >/tmp/restart.log
fi


