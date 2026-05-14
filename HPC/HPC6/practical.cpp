#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>

using namespace std;

int main()
{

    int n, k;

    cout << "Enter number of data points: ";
    cin >> n;

    cout << "Enter number of clusters: ";
    cin >> k;

    vector<int> data(n);
    vector<int> centroid(k);
    vector<int> cluster(n);

    cout << "Enter data points:\n";
    for (int i = 0; i < n; i++)
        cin >> data[i];

    cout << "Enter initial centroids:\n";
    for (int i = 0; i < k; i++)
        cin >> centroid[i];

#pragma omp parallel for
    for (int i = 0; i < n; i++)
    {

        int minDist = abs(data[i] - centroid[0]);
        int index = 0;

        for (int j = 1; j < k; j++)
        {

            int dist = abs(data[i] - centroid[j]);

            if (dist < minDist)
            {
                minDist = dist;
                index = j;
            }
        }

        cluster[i] = index;
    }

    cout << "\nCluster Assignment:\n";

    for (int i = 0; i < n; i++)
    {
        cout << "Data " << data[i]
             << " -> Cluster "
             << cluster[i] << endl;
    }

    return 0;
}
/*
 *
 *
 *
 OUTPUT:
Enter number of data points: 5
Enter number of clusters: 2
Enter data points:
1 2 10 12 14
Enter initial centroids:
2 12

Cluster Assignment:
Data 1 -> Cluster 0
Data 2 -> Cluster 0
Data 10 -> Cluster 1
Data 12 -> Cluster 1
Data 14 -> Cluster 1


 *
 *
 *
 */