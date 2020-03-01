/*
    The user must enter the parameters l, ω, the final time tf and the time step δt.
    Time taken as t0 = 0.
    The convention that we follow for the output of the results is that they should be written in a file where 7 columns are the values of: t, x, y, z, xz, vy and vz.

    File: Pendulum.cpp
        - Set pendulum angular velocity omega and display motion in 3D.
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cmath>

using namespace std;

auto constexpr M_PI = 3.14159265359;
auto constexpr g = 9.81;

int main()
{
    // Declaration of variables
    double l, r, x, y, z, vx, vy, vz, t, tf, dt;
    double theta, cos_theta, sin_theta, omega;
    string buf;

    // Ask user for input
    cout << "# Enter l, omega: \n";
    cin >> l >> omega;
    getline(cin, buf);

    cout << "# Enter tf, dt: \n";
    cin >> tf >> dt;
    getline(cin, buf);

    cout << "# l = " << l << " omega = " << omega << endl;

    cout << "# T = " << 2.0 * M_PI / omega << " omega_min = " << sqrt(g / l) << endl;

    cout << "# t0 = " << 0.0 << " tf = " << tf << " dt = " << dt << endl;

    // Initialize
    cos_theta = g / (omega * omega * l);

    if (cos_theta >= 1.0)
    {
        cerr << "cos(theta) >= 1 \n";
        exit(1);
    }

    sin_theta = sqrt(1.0 - cos_theta * cos_theta);
    z = -g / (omega * omega); // They remain constant throughout the motion
    vz = 0.0;
    r = g / (omega * omega) * sin_theta / cos_theta;

    ofstream os_file("ConicalPendulum.dat");
    os_file.precision(17);

    // Compute
    t = 0.0;

    while (t <= tf)
    {
        x = r * cos(omega * t);
        y = r * sin(omega * t);
        vx = -r * sin(omega * t) * omega;
        vy = r * cos(omega * t) * omega;

        os_file << t << " "
                << x << " " << y << " " << z << " "
                << vx << " " << vy << " " << vz << " " << endl;

        t = t + dt;
    }

    //getchar();

    exit(0);
}