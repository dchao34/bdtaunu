"""@package plotutils
Convenient plotting functions using Matplotlib.
"""

#! /Library/Frameworks/Python.framework/Versions/2.7/bin/python

import numpy as np
import matplotlib.pyplot as plt
from sklearn.neighbors import KernelDensity
from sklearn.grid_search import GridSearchCV


def SilvermanBandwidth(X):
    """Compute bandwidth for a Gaussian KDE with Silverman's rule.

    Parameters
    ----------
    X: Numpy array with shape (n, 1). This is the same as
       scikit-learn's convention for a single feature over
       all records.

    Returns
    -------
    Real number: The smoothing bandwidth of the input determined
                 using Silverman's rule.
    """
    return 1.06 * np.std(X) * (len(X) ** (-0.2))


def FreedmanDiaconisBinwidth(x):
    """Compute histogram binwidth using Freedman-Diaconis' rule.

    Parameters
    ----------
    x: Numpy array with shape (n, ).

    Returns
    -------
    Integer: The number of bins determined using Freedman-Diaconis'
             rule. The result is rounded down to the nearest integer.
    """
    hist_range = x.max() - x.min()
    IQR = np.percentile(x, 75) - np.percentile(x, 25)
    return int(hist_range / (2 * IQR * (len(x) ** (-1.0 / 3))))


def ExtractArrayByCategory(arr, varname, catname, cat_idx):
    """Extract a column from structured array for a specified category.

    Given a structured array, extract a specific column for a specific
    category of records. For example, return feature x for records that
    belong to category c.

    Parameters
    ----------
    arr: Numpy structured array.
    varname: Name of the column to extract.
    catname: Name of the column indicating the category of each record.
    cat_idx: The specific category of interest.

    Returns
    -------
    Numpy array: Shape is (n, ), where n is the number of records
                 belonging to the category of interest.
    """
    x, c = arr[varname], arr[catname]
    return x[c == cat_idx]


def StackByCategory(arr, varname, catname, wgtname=None,
                    cat_dict=None, ax=None, **kwargs):
    """Make a stacked histogram grouped by a specific category.

    Given a structured array, make a stacked histogram of a some
    variable grouped by some category. For example, make a stacked
    histogram of height grouped by species type.

    Parameters
    ----------
    arr: Numpy structured array.

    varname: Name of the column to histogram.

    catname: Name of the column with the categories to group by.

    wgtname: Name of the column containing observation weights.
             Defaults to weight 1 for all records.

    cat_dict: Dictionary that provides a mapping between specific
              category indices with a more descriptive label.

    ax: Plotting axis to draw on. Defaults to pyplot.gca().

    **kwargs: **kwargs for pyplot.hist().

    Returns
    -------
    (counts, bins, patches): Same as pyplot.hist().
    """

    if not ax:
        ax = plt.gca()

    x, c = arr[varname], arr[catname]
    x_i = [x[c == i] for i in np.unique(c)]

    labels = []
    if cat_dict:
        labels = [cat_dict[i] for i in map(int, np.unique(c))]
    else:
        labels = map(str, map(int, np.unique(c)))

    w_i = None
    if wgtname:
        w = arr[wgtname]
        w_i = [w[c == i] for i in np.unique(c)]

    counts, bins, patches = ax.hist(x_i, weights=w_i,
                                    stacked=True, label=labels,
                                    histtype='stepfilled', alpha=0.7,
                                    linewidth=0,
                                    **kwargs)

    ax.legend()
    ax.set_xlabel(varname)
    ax.set_ylabel('Stacked Counts')

    return counts, bins, patches


def NormByCategory(arr, varname, catname,
                   exclude=[], cat_dict=None,
                   ax=None,
                   **kwargs):
    """Make a normed histograms grouped by a specific category.

    Obsolete. Prefer using KdeByCategory to study densities.
    """

    if not ax:
        ax = plt.gca()

    x, c = arr[varname], arr[catname]

    cat = []
    for i in map(int, np.unique(c)):
        if i not in exclude:
            cat.append(i)

    x_i = [x[c == i] for i in cat]

    labels = []
    if cat_dict:
        labels = [cat_dict[i] for i in cat]
    else:
        labels = map(str, map(int, cat))

    counts, bins, patches = ax.hist(x_i, normed=True, label=labels,
                                    histtype='stepfilled',
                                    alpha=0.7, linewidth=0,
                                    **kwargs)

    ax.legend()
    ax.set_xlabel(varname)
    ax.set_ylabel('Probability Density')

    return counts, bins, patches


def KdeByCategory(arr, varname, catname,
                  exclude=[], cat_dict=None,
                  legend_loc=1, legend_size=12,
                  ax=None, xlim=None):
    """Estimate and plot probability densities grouped by category.

    Given a structured array, estimate and plot probability densities
    for a specific variable grouped by some category.

    The densities are estiamted using Gaussian kernels with
    Silverman's rule for bandwidth selection.

    Parameters
    ----------
    arr: Numpy structured array.

    varname: Name of the column to estimate the probability density.

    catname: Name of the column with the categories to group by.

    exclude: List of category indices to exclude from consideration.

    cat_dict: Dictionary that provides a mapping between specific
              category indices with a more descriptive label.

    ax: Plotting axis to draw on. Defaults to pyplot.gca().
    """

    if not ax:
        ax = plt.gca()

    if xlim:
        ax.set_xlim(xlim)

    x, c = arr[varname], arr[catname]

    cat = []
    for i in map(int, np.unique(c)):
        if i not in exclude:
            cat.append(i)

    x_i = [x[c == i] for i in cat]

    labels = []
    if cat_dict:
        labels = [cat_dict[i] for i in cat]
    else:
        labels = map(str, map(int, cat))

    kde_i = []
    for x in x_i:
        X = x[:, np.newaxis]
        kde_params = {'kernel': 'gaussian',
                      'bandwidth': SilvermanBandwidth(X),
                      'rtol': 1e-4}
        kde = KernelDensity(**kde_params).fit(X)
        kde_i.append(kde)

    X_plot = np.linspace(x.min(), x.max(), 1000)[:, np.newaxis]
    for kde, lab in zip(kde_i, labels):
        log_dens = kde.score_samples(X_plot)
        ax.plot(X_plot, np.exp(log_dens), linewidth=2, alpha=0.5, label=lab)

    ax.legend(loc=legend_loc, prop={'size': legend_size})
    ax.set_xlabel(varname)
    ax.set_ylabel('Probability Density')

    return


# Overlay histogram with Gaussian kernel density estimators.
def KdeOverHist(arr, varname, catname, cat_idx, cat_dict=None,
                silverman=True, bandwidths=[], cv=False, bins=None,
                legend_loc=1, legend_size=12,
                ax=None):
    """Plot estimated probability density overlayed on a histogram.

    Given a structured array, a specific variable, and a specific
    category, estimate and plot probability densities using various
    techniques and overlay the results on a histogram.

    The densities are estimated using Gaussian kernels. The various
    techniques are really various bandwidth selection techniques.

    Parameters
    ----------
    arr: Numpy structured array.

    varname: Name of the column to plot.

    catname: Name of the column with the category information.

    cat_idx: The specific index of the category of interest.

    cat_dict: Dictionary that provides a mapping between specific
              category indices with a more descriptive label.

    silverman: Use Silverman's rule to estimate the bandwidth.

    bandwidths: List of bandwidths to try. Manual "dial-in"s.

    cv: Use cross validation to estimate the bandwidth. See
        source for the details/parameters.

    bins: Number of bins for the histogram. If left alone,
          this defaults to the Freedman-Diaconis rule.

    ax: Plotting axis to draw on. Defaults to pyplot.gca().
    """

    if not ax:
        ax = plt.gca()

    x, c = arr[varname], arr[catname]
    x = x[c == cat_idx]

    X = x[:, np.newaxis]

    labels, kdes = [], []

    # User specified bandwidths
    for bw in bandwidths:
        params = {'kernel': 'gaussian', 'bandwidth': bw, 'rtol': 1e-4}
        kdes.append(KernelDensity(**params).fit(X))
        labels.append('h = {0}'.format(bw))

    # Silverman bandwidth
    if silverman:
        params = {'kernel': 'gaussian',
                  'bandwidth': SilvermanBandwidth(X),
                  'rtol': 1e-4}
        kdes.append(KernelDensity(**params).fit(X))
        labels.append(
            'h={0} (SR)'.format(
                round(SilvermanBandwidth(X), 2)))

    # Cross Validation bandwidth
    if cv:
        grid = GridSearchCV(KernelDensity(),
                            {'bandwidth': np.linspace(
                                SilvermanBandwidth(X) / 2.0,
                                SilvermanBandwidth(X) * 2.0,
                                30),
                             'rtol': [1e-4]},
                            cv=20)
        grid.fit(X)
        params = {'kernel': 'gaussian',
                  'bandwidth': grid.best_params_['bandwidth'],
                  'rtol': 1e-4}
        kdes.append(KernelDensity(**params).fit(X))
        labels.append(
            'h={0} (CV)'.format(
                round(grid.best_params_['bandwidth'], 2)))

    # Plot KDE results
    X_plot = np.linspace(x.min(), x.max(), 1000)[:, np.newaxis]
    for kde, lab in zip(kdes, labels):
        log_dens = kde.score_samples(X_plot)
        ax.plot(X_plot, np.exp(log_dens), linewidth=2, alpha=0.5, label=lab)

    # Plot histogram
    hist_label = 'B = {0}'
    if not bins:
        bins = FreedmanDiaconisBinwidth(x)
        hist_label += ' (FD)'
    hist_label = hist_label.format(bins)

    ax.hist(x, bins=bins, histtype='stepfilled',
            alpha=0.3, normed=True, fc='gray',
            linewidth=0,
            label=hist_label)

    # Legend
    ax.legend(loc=legend_loc, prop={'size': legend_size})

    # Plot format
    if cat_dict:
        ax.set_title('{0} category'.format(cat_dict[cat_idx]))
    else:
        ax.set_title('{0} category'.format(cat_idx))

    ax.set_xlabel(varname)
    ax.set_ylabel('Probability Density')

    return


if __name__ == '__main__':

    fig = plt.figure()
    #x = np.array([1, 1, 1, 3, 3, 4, 4, 4, 4, 4, 2, 2, 2, 2])
    #StackByCategory(x, bins=4, histtype='stepfilled', alpha=0.4)
    #plt.hist(x)
