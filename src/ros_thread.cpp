#include "include/ros_thread.h"

ROSThread::ROSThread(int argc, char** argv):
  m_argc(argc),
  m_argv(argv)
{

}

ROSThread::~ROSThread()
{
  if (ros::isStarted()) {
    ros::shutdown();
    ros::waitForShutdown();
  }
  m_pThread->quit();
}

bool ROSThread::init()
{
  m_pThread = new QThread();
  this->moveToThread(m_pThread);

  connect(m_pThread, &QThread::started, this, &ROSThread::run);
  ros::init(m_argc, m_argv, "iarc7_sim_node");

  if (!ros::master::check())
    return false;

  ros::start();
  ros::Time::init();
  ros::NodeHandle nh;
  sub_quad = nh.subscribe("/ground_truth/state", 10, &ROSThread::quadCallback, this);
  sub_gbot0 = nh.subscribe("/robot0/odom", 10, &ROSThread::gBot0Callback, this);
  sub_gbot1 = nh.subscribe("/robot1/odom", 10, &ROSThread::gBot1Callback, this);
  sub_gbot5 = nh.subscribe("/robot5/odom", 10, &ROSThread::gBot5Callback, this);

  m_pThread->start();
  return true;
}

void ROSThread::quadCallback(const nav_msgs::OdometryConstPtr& msg)
{
  QMutex * pMutex = new QMutex();

  pMutex->lock();
  Pose p;
  p.x = msg->pose.pose.position.x;
  p.y = msg->pose.pose.position.y;
  p.z = msg->pose.pose.position.z;
  p.quat_w = msg->pose.pose.orientation.w;
  p.quat_x = msg->pose.pose.orientation.x;
  p.quat_y = msg->pose.pose.orientation.y;
  p.quat_z = msg->pose.pose.orientation.z;
  p.velocity.lin_x = msg->twist.twist.linear.x;
  p.velocity.lin_y = msg->twist.twist.linear.y;
  p.velocity.lin_z = msg->twist.twist.linear.z;
  p.velocity.ang_x = msg->twist.twist.angular.x;
  p.velocity.ang_y = msg->twist.twist.angular.y;
  p.velocity.ang_z = msg->twist.twist.angular.z;
  for (int i = 0; i < 36; i++)
    p.covariance[i] = (double)msg->pose.covariance[i];
  common->setQuadPose(p);
  pMutex->unlock();

  delete pMutex;
  Q_EMIT newPose();
}

void ROSThread::gBot0Callback(const nav_msgs::OdometryConstPtr& msg)
{
  QMutex * pMutex = new QMutex();

  pMutex->lock();
  Pose p;
  p.x = msg->pose.pose.position.x;
  p.y = msg->pose.pose.position.y;
  p.z = msg->pose.pose.position.z;
  p.quat_w = msg->pose.pose.orientation.w;
  p.quat_x = msg->pose.pose.orientation.x;
  p.quat_y = msg->pose.pose.orientation.y;
  p.quat_z = msg->pose.pose.orientation.z;
  p.velocity.lin_x = msg->twist.twist.linear.x;
  p.velocity.lin_y = msg->twist.twist.linear.y;
  p.velocity.lin_z = msg->twist.twist.linear.z;
  p.velocity.ang_x = msg->twist.twist.angular.x;
  p.velocity.ang_y = msg->twist.twist.angular.y;
  p.velocity.ang_z = msg->twist.twist.angular.z;
  for (int i = 0; i < 36; i++)
    p.covariance[i] = (double)msg->pose.covariance[i];
  common->setgBot0Pose(p);
  pMutex->unlock();

  delete pMutex;
  Q_EMIT newPose();
}

void ROSThread::gBot1Callback(const nav_msgs::OdometryConstPtr& msg)
{
  QMutex * pMutex = new QMutex();

  pMutex->lock();
  Pose p;
  p.x = msg->pose.pose.position.x;
  p.y = msg->pose.pose.position.y;
  p.z = msg->pose.pose.position.z;
  p.quat_w = msg->pose.pose.orientation.w;
  p.quat_x = msg->pose.pose.orientation.x;
  p.quat_y = msg->pose.pose.orientation.y;
  p.quat_z = msg->pose.pose.orientation.z;
  p.velocity.lin_x = msg->twist.twist.linear.x;
  p.velocity.lin_y = msg->twist.twist.linear.y;
  p.velocity.lin_z = msg->twist.twist.linear.z;
  p.velocity.ang_x = msg->twist.twist.angular.x;
  p.velocity.ang_y = msg->twist.twist.angular.y;
  p.velocity.ang_z = msg->twist.twist.angular.z;
  for (int i = 0; i < 36; i++)
    p.covariance[i] = (double)msg->pose.covariance[i];
  common->setgBot1Pose(p);
  pMutex->unlock();

  delete pMutex;
  Q_EMIT newPose();
}

void ROSThread::gBot5Callback(const nav_msgs::OdometryConstPtr& msg)
{
  QMutex * pMutex = new QMutex();

  pMutex->lock();
  Pose p;
  p.x = msg->pose.pose.position.x;
  p.y = msg->pose.pose.position.y;
  p.z = msg->pose.pose.position.z;
  p.quat_w = msg->pose.pose.orientation.w;
  p.quat_x = msg->pose.pose.orientation.x;
  p.quat_y = msg->pose.pose.orientation.y;
  p.quat_z = msg->pose.pose.orientation.z;
  p.velocity.lin_x = msg->twist.twist.linear.x;
  p.velocity.lin_y = msg->twist.twist.linear.y;
  p.velocity.lin_z = msg->twist.twist.linear.z;
  p.velocity.ang_x = msg->twist.twist.angular.x;
  p.velocity.ang_y = msg->twist.twist.angular.y;
  p.velocity.ang_z = msg->twist.twist.angular.z;
  for (int i = 0; i < 36; i++)
    p.covariance[i] = (double)msg->pose.covariance[i];
  common->setgBot5Pose(p);
  pMutex->unlock();

  delete pMutex;
  Q_EMIT newPose();
}

void ROSThread::run()
{
  ros::Rate loop_rate(10);
  QMutex * pMutex;
  while (ros::ok()) {
    pMutex = new QMutex();

    pMutex->lock();

    pMutex->unlock();

    ros::spinOnce();
    loop_rate.sleep();
    delete pMutex;
  }
}
