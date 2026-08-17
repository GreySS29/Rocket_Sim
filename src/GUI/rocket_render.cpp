#include "../../include/GUI/RocketRender.h"

vector<std::pair<double,double>> RocketRender::get_max_min_traj () const{

    double minX = trajectory[0].first, maxX = trajectory[0].first;
    double minY = trajectory[0].second, maxY = trajectory[0].second;

    for (const auto& p : trajectory) {
        //if (p.first < minX) minX = p.first;
        if (p.first > maxX) maxX = p.first;
        //if (p.second < minY) minY = p.second;
        if (p.second > maxY) maxY = p.second;
    }
    // min quantities is start position 

    std::pair<double,double> min {minX,minY};
    std::pair<double,double> max {maxX,maxY};
    return  {min,max};
    
}

void RocketRender::put_force_buffer(std::ofstream& ofs) const
{
    if(g_force.size()!=a_force.size() && g_force.size()!=f_force.size() )
    {

        std::cerr << "sizes between g_force and a_force don't equal";
        return ;
    }
    for(size_t i =0; i<g_force.size(); ++i)
    {
        ofs << "G_force" << g_force[i] << "\t"
        << "A_force" << a_force[i] << '\t'
        << "F_force" << f_force[i] << '\n';
        

    }
}

void RocketRender::drawHeightOverTime(double dt) const
{
    if (trajectory.empty()) {
        return;
    }
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_STRIP);

    for (std::size_t i = 0; i < trajectory.size(); ++i) {
        const double time = static_cast<double>(i) * dt;
        const double height = trajectory[i].second;
        glVertex2d(time, height);
    }   

    glEnd();
}    

void RocketRender::drawRocket() const 
{
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);

    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(0.0f, 1.0f);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glEnd();

    glPopMatrix();
}

void RocketRender::drawTrajectory() const
{
    if (trajectory.size() < 2) {
        std::cerr << "No data"<<'\n';
        return;
    }
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_LINE_STRIP);
    for (const auto& p : trajectory) {
        glVertex2f(static_cast<float>(p.first), static_cast<float>(p.second));
    }
    glEnd();
}

void RocketRender::print_trajectory () const 
{
    for (std::pair x : trajectory)
    {
        std::cout<< "|" << x.first <<"  :  "<< x.second<< "|\t"; 
    }
}


